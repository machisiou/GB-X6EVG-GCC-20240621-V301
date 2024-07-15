/**
 * @file UART.h
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief UART function declaration 
 * @date 2024-02-29
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __RTS5911__
// UARTPWR
#define UART_DEFAULT_UARTPWR_PWR_DI (0U)
#define UART_DEFAULT_UARTPWR_PWR_EN (1U)
#define UART_DEFAULT_UARTPWR_CLK_25M (0U)
#define UART_DEFAULT_UARTPWR_CLK_100M (1U)
#define UART_DEFAULT_UARTPWR_DIV_BY_1 (0U)
#define UART_DEFAULT_UARTPWR_DIV_BY_2 (1U)
#define UART_DEFAULT_UARTPWR_DIV_BY_4 (2U)
#define UART_DEFAULT_UARTPWR_DIV_BY_8 (3U)
#define UART_DEFAULT_UARTPWR_CLKSRC UART_DEFAULT_UARTPWR_CLK_100M
#define UART_DEFAULT_UARTPWR_DIV UART_DEFAULT_UARTPWR_DIV_BY_2
// GPIO
#define UART_GPIO_RX_NUM (113U)
#define UART_GPIO_RX_MULTIFUNC_NUM (1U)
#define UART_GPIO_TX_NUM (114U)
#define UART_GPIO_TX_MULTIFUNC_NUM (1U)
#define GPIO_3_3V_MODE (0U)
#define GPIO_OUTPUT_TYPE_PUSH_PULL (0U)
#else
#error "unknown cpu identity detected"
#endif

#define UART_DATA_LENGTH_5_BITS (0b00)
#define UART_DATA_LENGTH_6_BITS (0b01)
#define UART_DATA_LENGTH_7_BITS (0b10)
#define UART_DATA_LENGTH_8_BITS (0b11)
#define UART_PARITY_DI (0)
#define UART_PARITY_EN (1)
#define UART_STOP_1_BIT (0)
#define UART_STOP_1_5_BIT (1)

#define UART_INTERRUPT_ID_THR_EMPTY (0b0010)
#define UART_INTERRUPT_ID_RECEIVED_DATA_AVAILABLE (0b0100)

typedef enum {
    UART_BAUDRATE_115200,   /*!< baudrate 115200 bps */
    UART_BAUDRATE_57600,    /*!< baudrate 57600 bps */
    UART_BAUDRATE_9600,     /*!< baudrate 9600 bps */
} UART_BAUDRATE;

typedef enum {
    UART_ERRORCODE_NO_ERROR,                    /*!< no error */
    UART_ERRORCODE_UNSUPPORTED_BAUDRATE,        /*!< unsupported baudrate */
    UART_ERRORCODE_UNSUPPORTED_CLOCK_SOURCE,    /*!< unsupported hardware clock source */
    UART_ERRORCODE_IMPRECISE_BAUDRATE,          /*!< imprecise baudrate is calculated */
    UART_ERRORCODE_RXFIFO_EMPTY,                /*!< UART RX FIFO is empty */
    UART_ERRORCODE_RX_READ_COMPLETE,            /*!< UART RX FIFO read is finished */
    UART_ERRORCODE_RX_RECV_BUFF_FULL,           /*!< Received buffer is full */
    UART_ERRORCODE_RX_NULL_RECV_BUFF,           /*!< Received buffer parameter is invalid */
} UART_ERRORCODE;

/**
 * @brief Configure UART peripheral regsiter and related peripheral registers.
 * @details This function configures power module and GPIOs related to UART.
 * And then calculate an appropriate dividor latch according to baudrate parameter.
 * The function configures UART with FIFO mode, 7-bits data length, parityless and 
 * 1-bit stop.
 * @param baudrate
 *     @arg @ref UART_BAUDRATE_115200
 *     @arg @ref UART_BAUDRATE_57600
 *     @arg @ref UART_BAUDRATE_9600
 * @retval
 *     @arg @ref UART_ERRORCODE_NO_ERROR
 *     @arg @ref UART_ERRORCODE_IMPRECISE_BAUDRATE
 *     @arg @ref UART_ERRORCODE_UNSUPPORTED_BAUDRATE
 *     @arg @ref UART_ERRORCODE_UNSUPPORTED_CLOCK_SOURCE
 */
UART_ERRORCODE UART_Init(UART_BAUDRATE baud_rate);

/**
 * @brief Write single character through UART protocol
 * @param byte 
 * @retval
 *     @arg @ref UART_ERRORCODE_NO_ERROR
 */
UART_ERRORCODE UART_Write_Char(const uint8_t byte);

/**
 * @brief Write string through UART protocol
 * @param string 
 * @retval
 *     @arg @ref UART_ERRORCODE_NO_ERROR
 */
UART_ERRORCODE UART_Write_String(char* string);

/**
 * @brief Generic UART Write function
 * @param TEXT char | string 
 */
#define UART_Write(TEXT) _Generic((TEXT),       \
    uint8_t: UART_Write_Char,                   \
    char: UART_Write_Char,                      \
    char*: UART_Write_String,                   \
    char [sizeof(TEXT)]: UART_Write_String,     \
    uint8_t [sizeof(TEXT)]: UART_Write_String,  \
    uint8_t*: UART_Write_String,                \
    int: UART_Write_Char,                       \
    uint32_t: UART_Write_Char                   \
    ) (TEXT)

/**
 * @brief Read character stream into character buffer through UART protocol
 * @param rxbuf character buffer 
 * @param rxbuf_size size of character buffer 
 * @param recv_byte actual byte count of UART read
 * @retval
 *     @arg @ref UART_ERRORCODE_RXFIFO_EMPTY
 *     @arg @ref UART_ERRORCODE_RX_NULL_RECV_BUFF
 *     @arg @ref UART_ERRORCODE_RX_RECV_BUFF_FULL
 *     @arg @ref UART_ERRORCODE_RX_CONTAIN_DATA
 */
UART_ERRORCODE UART_Read(uint8_t* rxbuf, size_t rxbuf_size, size_t* recv_byte);