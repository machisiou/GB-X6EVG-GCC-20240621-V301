/**
 * @file UART.c
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief UART function implementation
 * @date 2024-02-29
 * @copyright Copyright (c) 2024
 */

#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "hal/UART.h"
#include "chip/rts5911/RTS5911.h"

typedef union
{
    struct {
        uint8_t DivL;
        uint8_t DivH;
        uint8_t ErrorCode;
        uint8_t Res0;
    };
    uint8_t bytes[4];
    uint32_t u32;
} dividor_latch;

_Static_assert(sizeof(dividor_latch) == sizeof(uint32_t), "dividor_latch isn't 4 bytes");

/**
 * @brief Calculate dividor latch according to baudrate input
 * @param baudrate
 *     @arg @ref UART_BAUDRATE_115200
 *     @arg @ref UART_BAUDRATE_57600
 *     @arg @ref UART_BAUDRATE_9600
 * @return dividor_latch 
 */
static dividor_latch
UART_Get_Dividor_Latch(const UART_BAUDRATE baudrate)
{
    dividor_latch latch = {.u32 = 0U};
    float bps, target_bps, quotient;

    switch (SYSTEM->UARTCLKPWR_b.CLKSRC)
    {
    case UART_DEFAULT_UARTPWR_CLK_25M:
        bps = 1600000.0f;
        break;
    case UART_DEFAULT_UARTPWR_CLK_100M:
        bps = 6400000.0f;
        break;
    default:
        latch.ErrorCode = UART_ERRORCODE_UNSUPPORTED_CLOCK_SOURCE;
        return latch;
    }
    // Tweak by ClKDiv
    bps /= (1 << SYSTEM->UARTCLKPWR_b.DIV);

    switch (baudrate)
    {
    case UART_BAUDRATE_115200:
        target_bps = 115200.0f;
        break;
    case UART_BAUDRATE_57600:
        target_bps = 57600.0f;
        break;
    case UART_BAUDRATE_9600:
        target_bps = 9600.0f;
        break;
    default:
        assert(false && "Unsupported baudrate detected");
        latch.ErrorCode = UART_ERRORCODE_UNSUPPORTED_BAUDRATE;
        return latch;
    }

    quotient = bps / target_bps;

    // Make sure that baudrate is computable with current clock source and dividor
    if(quotient >= 1.0) 
    {
        latch.u32 = (uint32_t) roundf(quotient);
        // Make sure latch dividor is accommodated into two bytes without overflow
        if(latch.ErrorCode == 0U && latch.Res0 == 0U)
            latch.ErrorCode = UART_ERRORCODE_NO_ERROR;
        else 
        {
            latch.Res0 = 0;
            latch.ErrorCode = UART_ERRORCODE_IMPRECISE_BAUDRATE;
        }
    }
    else
    {
        assert(false && "Can't calculate such baudrate with current latch dividor value and clock source");
        latch.ErrorCode = UART_ERRORCODE_IMPRECISE_BAUDRATE;
    }
    
    return latch;
}

/**
 * @brief Apply patch for JTAG/SWD debug if debug mode is enabled
 */
static void
UART_ApplyPatchForDebug()
{
    // RIDE read write-only register FCR in debug mode and make UART register broken.
    // Here applys a debug patch to make UART registers debuggable.
    if(DCB->DHCSR & DCB_DHCSR_C_DEBUGEN_Msk)
    {
        UART->FCR = 0;
        UART->LCR_b.DLAB = 1;
        UART->DLL_b.DIVL = 0x01;
        UART->LCR_b.DLAB = 0;
        UART->FCR_b.FIFOE = 1;
    }
}

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

UART_ERRORCODE 
UART_Init(const UART_BAUDRATE baudrate)
{
    // Enable UART power if not present
    if(!SYSTEM->UARTCLKPWR_b.PWR)
    {
        SYSTEM->UARTCLKPWR_b.PWR = UART_DEFAULT_UARTPWR_PWR_EN;
        SYSTEM->UARTCLKPWR_b.CLKSRC = UART_DEFAULT_UARTPWR_CLKSRC;
        SYSTEM->UARTCLKPWR_b.DIV = UART_DEFAULT_UARTPWR_DIV;
    }

    // Enable UART TX GPIO if not present
    if(GPIO->GCR_b[UART_GPIO_TX_NUM].MFCTRL != UART_GPIO_TX_MULTIFUNC_NUM)
    {
        GPIO->GCR_b[UART_GPIO_TX_NUM].MFCTRL = UART_GPIO_TX_MULTIFUNC_NUM;
        GPIO->GCR_b[UART_GPIO_TX_NUM].INVOLMD = GPIO_3_3V_MODE;
        GPIO->GCR_b[UART_GPIO_TX_NUM].OUTTYPCTRL = GPIO_OUTPUT_TYPE_PUSH_PULL;
    }

    // Enable UART RX GPIO if not present
    if(GPIO->GCR_b[UART_GPIO_RX_NUM].MFCTRL != UART_GPIO_RX_MULTIFUNC_NUM)
    {
        GPIO->GCR_b[UART_GPIO_RX_NUM].MFCTRL = UART_GPIO_RX_MULTIFUNC_NUM;
        GPIO->GCR_b[UART_GPIO_RX_NUM].INVOLMD = GPIO_3_3V_MODE;
        GPIO->GCR_b[UART_GPIO_RX_NUM].OUTTYPCTRL = GPIO_OUTPUT_TYPE_PUSH_PULL;
    }

    dividor_latch latch = UART_Get_Dividor_Latch(baudrate);
    // byte 3 (Res0) must be invalid
    assert(latch.Res0 == 0);

    // Check dividor latch
    if(latch.ErrorCode != UART_ERRORCODE_NO_ERROR) 
        return latch.ErrorCode;

    // Fix DLAB can't be properly written in debug mode
    UART_ApplyPatchForDebug();

    // Write to Modem Control Register (MCR) to program SIR mode, auto flow, 
    // loopback, modem control outputs
    UART->MCR_b.RTS = 1;    // request-to-send
    UART->MCR_b.AFCE = 1;   // auto flow control

    // Modify dividor latch
    UART->LCR_b.DLAB = 1;
    UART->DLL_b.DIVL = latch.DivL;
    UART->DLH_b.DIVH = latch.DivH;
    UART->LCR_b.DLAB = 0;

    // Set up transfer characteristics
    UART->LCR_b.DLS = UART_DATA_LENGTH_7_BITS;
    UART->LCR_b.PEN = UART_PARITY_DI;
    UART->LCR_b.STOP = UART_STOP_1_BIT;

    // Write to FCR to enable FIFOs and set Transmit FIFO threshold level
    UART->FCR_b.FIFOE = 1;

    // Write to IER to enable required interrupt
    UART->IER_b.ETBEI = 1; // Transmit interrupt
    UART->IER_b.ERBFI = 1; // Receive Available interrupt

    return UART_ERRORCODE_NO_ERROR;
}

UART_ERRORCODE
UART_Write_Char(const uint8_t byte)
{
    // Write characters to be transmitted to transmit FIFO by writing to THR
    UART->THR = byte;
    // Wait for Transmit Holding Register empty interrupt (IIR[3:0] = 4’b0010)
    while(UART->IIR_b.IID & UART_INTERRUPT_ID_THR_EMPTY);
    // Clear THR empty interrupt by reading IIR register
    (volatile uint32_t) UART->IIR;
    return UART_ERRORCODE_NO_ERROR;
}

UART_ERRORCODE
UART_Write_String(char* string)
{
    while(*string != '\0')
    {
        // Write characters to be transmitted to transmit FIFO by writing to THR
        UART->THR = *string;
        // Wait for Transmit Holding Register empty interrupt (IIR[3:0] = 4’b0010)
        while(UART->IIR_b.IID & UART_INTERRUPT_ID_THR_EMPTY);
        // Next character
        string++;
    }
    // Clear THR empty interrupt by reading IIR register
    (volatile uint32_t) UART->IIR;
    return UART_ERRORCODE_NO_ERROR;
}

UART_ERRORCODE
UART_Read(uint8_t* rxbuf, size_t rxbuf_size, size_t* recv_byte)
{
    // Check RX FIFO empty
    if(UART->USR_b.RFNE == 0)
        return UART_ERRORCODE_RXFIFO_EMPTY;

    // Check null pointer
    if(rxbuf == NULL)
        return UART_ERRORCODE_RX_NULL_RECV_BUFF;

    size_t recv_count = 0;

    while(UART->USR_b.RFNE == 1)
    {
        if(rxbuf_size < recv_count)
        {
            if(recv_byte != NULL)
                *recv_byte = rxbuf_size;
            return UART_ERRORCODE_RX_RECV_BUFF_FULL;        
        }
        rxbuf[recv_count] = UART->RBR_b.DATA;
        recv_count++;
    }

    if(recv_byte != NULL)
        *recv_byte = recv_count;
    return UART_ERRORCODE_RX_READ_COMPLETE;
}