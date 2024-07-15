;/**************************************************************************//**
; * @file     startup_RTS5911.s
; * @brief    CMSIS Core Device Startup File for
; *           Realtek RTS5911 Device
; * @version  V1.03
; * @date     07. April 2016
; ******************************************************************************/
;/* Copyright (c) 2015 - 2016 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/

                .syntax  unified
                .arch    armv8-m.main

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop			    /*     Initial Stack Pointer   */
                .long    Reset_Handler          /*     Reset Handler           */
                .long    NMI_Handler            /*     NMI Handler             */
                .long    HardFault_Handler      /*     Hard Fault Handler      */
                .long    MemManage_Handler      /*     MPU Fault Handler       */
                .long    BusFault_Handler       /*     Bus Fault Handler       */
                .long    UsageFault_Handler     /*     Usage Fault Handler     */
                .long    SecureFault_Handler    /*     Secure Fault Handler    */
                .long    0                      /*     Reserved                */
                .long    0                      /*     Reserved                */
                .long    0                      /*     Reserved                */
                .long    SVC_Handler            /*     SVCall Handler          */
                .long    DebugMon_Handler       /*     Debug Monitor Handler   */
                .long    0                      /*     Reserved                */
                .long    PendSV_Handler         /*     PendSV Handler          */
                .long    SysTick_Handler        /*     SysTick Handler         */

                /* Interrupts */
                .long    GPIO000_Handler        /*     000 GPIO000 Handler     */
                .long    GPIO001_Handler        /*     001 GPIO001 Handler     */
                .long    GPIO002_Handler        /*     002 GPIO002 Handler     */
                .long    GPIO003_Handler        /*     003 GPIO003 Handler     */
                .long    GPIO004_Handler        /*     004 GPIO004 Handler     */
                .long    GPIO005_Handler        /*     005 GPIO005 Handler     */
                .long    GPIO006_Handler        /*     006 GPIO006 Handler     */
                .long    GPIO007_Handler        /*     007 GPIO007 Handler     */
                .long    GPIO008_Handler        /*     008 GPIO008 Handler     */
                .long    GPIO009_Handler        /*     009 GPIO009 Handler     */
                .long    GPIO010_Handler        /*     010 GPIO010 Handler     */
                .long    GPIO011_Handler        /*     011 GPIO011 Handler     */
                .long    GPIO012_Handler        /*     012 GPIO012 Handler     */
                .long    GPIO013_Handler        /*     013 GPIO013 Handler     */
                .long    GPIO014_Handler        /*     014 GPIO014 Handler     */
                .long    GPIO015_Handler        /*     015 GPIO015 Handler     */
                .long    GPIO016_Handler        /*     016 GPIO016 Handler     */
                .long    GPIO017_Handler        /*     017 GPIO017 Handler     */
                .long    GPIO018_Handler        /*     018 GPIO018 Handler     */
                .long    GPIO019_Handler        /*     019 GPIO019 Handler     */
                .long    GPIO020_Handler        /*     020 GPIO020 Handler     */
                .long    GPIO021_Handler        /*     021 GPIO021 Handler     */
                .long    GPIO022_Handler        /*     022 GPIO022 Handler     */
                .long    GPIO023_Handler        /*     023 GPIO023 Handler     */
                .long    GPIO024_Handler        /*     024 GPIO024 Handler     */
                .long    GPIO025_Handler        /*     025 GPIO025 Handler     */
                .long    GPIO026_Handler        /*     026 GPIO026 Handler     */
                .long    GPIO027_Handler        /*     027 GPIO027 Handler     */
                .long    GPIO028_Handler        /*     028 GPIO028 Handler     */
                .long    GPIO029_Handler        /*     029 GPIO029 Handler     */
                .long    GPIO030_Handler        /*     030 GPIO030 Handler     */
                .long    GPIO031_Handler        /*     031 GPIO031 Handler     */
                .long    GPIO032_Handler        /*     032 GPIO032 Handler     */
                .long    GPIO033_Handler        /*     033 GPIO033 Handler     */
                .long    GPIO034_Handler        /*     034 GPIO034 Handler     */
                .long    GPIO035_Handler        /*     035 GPIO035 Handler     */
                .long    GPIO036_Handler        /*     036 GPIO036 Handler     */
                .long    GPIO037_Handler        /*     037 GPIO037 Handler     */
                .long    GPIO038_Handler        /*     038 GPIO038 Handler     */
                .long    GPIO039_Handler        /*     039 GPIO039 Handler     */
                .long    GPIO040_Handler        /*     040 GPIO040 Handler     */
                .long    GPIO041_Handler        /*     041 GPIO041 Handler     */
                .long    GPIO042_Handler        /*     042 GPIO042 Handler     */
                .long    GPIO043_Handler        /*     043 GPIO043 Handler     */
                .long    GPIO044_Handler        /*     044 GPIO044 Handler     */
                .long    GPIO045_Handler        /*     045 GPIO045 Handler     */
                .long    GPIO046_Handler        /*     046 GPIO046 Handler     */
                .long    GPIO047_Handler        /*     047 GPIO047 Handler     */
                .long    GPIO048_Handler        /*     048 GPIO048 Handler     */
                .long    GPIO049_Handler        /*     049 GPIO049 Handler     */
                .long    GPIO050_Handler        /*     050 GPIO050 Handler     */
                .long    GPIO051_Handler        /*     051 GPIO051 Handler     */
                .long    GPIO052_Handler        /*     052 GPIO052 Handler     */
                .long    GPIO053_Handler        /*     053 GPIO053 Handler     */
                .long    GPIO054_Handler        /*     054 GPIO054 Handler     */
                .long    GPIO055_Handler        /*     055 GPIO055 Handler     */
                .long    GPIO056_Handler        /*     056 GPIO056 Handler     */
                .long    GPIO057_Handler        /*     057 GPIO057 Handler     */
                .long    GPIO058_Handler        /*     058 GPIO058 Handler     */
                .long    GPIO059_Handler        /*     059 GPIO059 Handler     */
                .long    GPIO060_Handler        /*     060 GPIO060 Handler     */
                .long    GPIO061_Handler        /*     061 GPIO061 Handler     */
                .long    GPIO062_Handler        /*     062 GPIO062 Handler     */
                .long    GPIO063_Handler        /*     063 GPIO063 Handler     */
                .long    GPIO064_Handler        /*     064 GPIO064 Handler     */
                .long    GPIO065_Handler        /*     065 GPIO065 Handler     */
                .long    GPIO066_Handler        /*     066 GPIO066 Handler     */
                .long    GPIO067_Handler        /*     067 GPIO067 Handler     */
                .long    GPIO068_Handler        /*     068 GPIO068 Handler     */
                .long    GPIO069_Handler        /*     069 GPIO069 Handler     */
                .long    GPIO070_Handler        /*     070 GPIO070 Handler     */
                .long    GPIO071_Handler        /*     071 GPIO071 Handler     */
                .long    GPIO072_Handler        /*     072 GPIO072 Handler     */
                .long    GPIO073_Handler        /*     073 GPIO073 Handler     */
                .long    GPIO074_Handler        /*     074 GPIO074 Handler     */
                .long    GPIO075_Handler        /*     075 GPIO075 Handler     */
                .long    GPIO076_Handler        /*     076 GPIO076 Handler     */
                .long    GPIO077_Handler        /*     077 GPIO077 Handler     */
                .long    GPIO078_Handler        /*     078 GPIO078 Handler     */
                .long    GPIO079_Handler        /*     079 GPIO079 Handler     */
                .long    GPIO080_Handler        /*     080 GPIO080 Handler     */
                .long    GPIO081_Handler        /*     081 GPIO081 Handler     */
                .long    GPIO082_Handler        /*     082 GPIO082 Handler     */
                .long    GPIO083_Handler        /*     083 GPIO083 Handler     */
                .long    GPIO084_Handler        /*     084 GPIO084 Handler     */
                .long    GPIO085_Handler        /*     085 GPIO085 Handler     */
                .long    GPIO086_Handler        /*     086 GPIO086 Handler     */
                .long    GPIO087_Handler        /*     087 GPIO087 Handler     */
                .long    GPIO088_Handler        /*     088 GPIO088 Handler     */
                .long    GPIO089_Handler        /*     089 GPIO089 Handler     */
                .long    GPIO090_Handler        /*     090 GPIO090 Handler     */
                .long    GPIO091_Handler        /*     091 GPIO091 Handler     */
                .long    GPIO092_Handler        /*     092 GPIO092 Handler     */
                .long    GPIO093_Handler        /*     093 GPIO093 Handler     */
                .long    GPIO094_Handler        /*     094 GPIO094 Handler     */
                .long    GPIO095_Handler        /*     095 GPIO095 Handler     */
                .long    GPIO096_Handler        /*     096 GPIO096 Handler     */
                .long    GPIO097_Handler        /*     097 GPIO097 Handler     */
                .long    GPIO098_Handler        /*     098 GPIO098 Handler     */
                .long    GPIO099_Handler        /*     099 GPIO099 Handler     */
                .long    GPIO100_Handler        /*     100 GPIO100 Handler     */
                .long    GPIO101_Handler        /*     101 GPIO101 Handler     */
                .long    GPIO102_Handler        /*     102 GPIO102 Handler     */
                .long    GPIO103_Handler        /*     103 GPIO103 Handler     */
                .long    GPIO104_Handler        /*     104 GPIO104 Handler     */
                .long    GPIO105_Handler        /*     105 GPIO105 Handler     */
                .long    GPIO106_Handler        /*     106 GPIO106 Handler     */
                .long    GPIO107_Handler        /*     107 GPIO107 Handler     */
                .long    GPIO108_Handler        /*     108 GPIO108 Handler     */
                .long    GPIO109_Handler        /*     109 GPIO109 Handler     */
                .long    GPIO110_Handler        /*     110 GPIO110 Handler     */
                .long    GPIO111_Handler        /*     111 GPIO111 Handler     */
                .long    GPIO112_Handler        /*     112 GPIO112 Handler     */
                .long    GPIO113_Handler        /*     113 GPIO113 Handler     */
                .long    GPIO114_Handler        /*     114 GPIO114 Handler     */
                .long    GPIO115_Handler        /*     115 GPIO115 Handler     */
                .long    GPIO116_Handler        /*     116 GPIO116 Handler     */
                .long    GPIO117_Handler        /*     117 GPIO117 Handler     */
                .long    GPIO118_Handler        /*     118 GPIO118 Handler     */
                .long    GPIO119_Handler        /*     119 GPIO119 Handler     */
                .long    GPIO120_Handler        /*     120 GPIO120 Handler     */
                .long    GPIO121_Handler        /*     121 GPIO121 Handler     */
                .long    GPIO122_Handler        /*     122 GPIO122 Handler     */
                .long    GPIO123_Handler        /*     123 GPIO123 Handler     */
                .long    GPIO124_Handler        /*     124 GPIO124 Handler     */
                .long    GPIO125_Handler        /*     125 GPIO125 Handler     */
                .long    GPIO126_Handler        /*     126 GPIO126 Handler     */
                .long    GPIO127_Handler        /*     127 GPIO127 Handler     */
                .long    GPIO128_Handler        /*     128 GPIO128 Handler     */
                .long    GPIO129_Handler        /*     129 GPIO129 Handler     */
                .long    GPIO130_Handler        /*     130 GPIO130 Handler     */
                .long    GPIO131_Handler        /*     131 GPIO131 Handler     */
                .long    0                      /*     132 Reserved            */
                .long    ERST_Handler           /*     133 eSPI Reset Pin Interrupt Handler                */
                .long    EPRCH_Handler          /*     134 eSPI Peripheral Ch. Interrupt Handler           */
                .long    EVCHIDX61_Handler      /*     135 eSPI Virtual Wire Ch. Index61 Interrupt Handler */
                .long    EVCHIDX51_Handler      /*     136 eSPI Virtual Wire Ch. Index51 Interrupt Handler */
                .long    EVCHIDX4A_Handler      /*     137 eSPI Virtual Wire Ch. Index4A Interrupt Handler */
                .long    EVCHIDX47_Handler      /*     138 eSPI Virtual Wire Ch. Index47 Interrupt Handler */
                .long    EVCHIDX44_Handler      /*     139 eSPI Virtual Wire Ch. Index44 Interrupt Handler */
                .long    EVCHIDX43_Handler      /*     140 eSPI Virtual Wire Ch. Index43 Interrupt Handler */
                .long    EVCHIDX42_Handler      /*     141 eSPI Virtual Wire Ch. Index42 Interrupt Handler */
                .long    EVCHIDX41_Handler      /*     142 eSPI Virtual Wire Ch. Index41 Interrupt Handler */
                .long    EVCHIDX7_Handler       /*     143 eSPI Virtual Wire Ch. Index7 Interrupt Handler  */
                .long    EVCHIDX3_Handler       /*     144 eSPI Virtual Wire Ch. Index3 Interrupt Handler  */
                .long    EVCHIDX2_Handler       /*     145 eSPI Virtual Wire Ch. Index2 Interrupt Handler  */
                .long    EVCH_Handler           /*     146 eSPI Virtual Wire Ch. Interrupt Handler         */
                .long    EOCHTX_Handler         /*     147 eSPI OOB Ch. Tx Interrupt Handler               */
                .long    EOCHRX_Handler         /*     148 eSPI OOB Ch. Rx Interrupt Handler               */
                .long    EOCHCFGEN_Handler      /*     149 eSPI OOB Ch. Conf Enable Change Interrupt Handler */
                .long    EFSAFSTR_Handler       /*     150 eSPI SAFS TR Interrupt Handler                  */
                .long    EFSAFSERASE_Handler    /*     151 eSPI SAFS Erase Interrupt Handler               */
                .long    EFMAFSTR_Handler       /*     152 eSPI MAFS TR Interrupt Handler                  */
                .long    EFCHCHG_Handler        /*     153 eSPI Flash Chanel Change Interrupt Handler      */
                .long    KBC_IB_Handler         /*     154 KBC Input Buffer Interrupt Handler              */
                .long    KBC_OB_Handler         /*     155 KBC Output Buffer Interrupt Handler             */
                .long    ACPI_IB_Handler        /*     156 ACPI Input Buffer Interrupt Handler             */
                .long    ACPI_OB_Handler        /*     157 ACPI Output Buffer Interrupt Handler            */
                .long    PMPORT0_IB_Handler     /*     158 PMPORT1 Input Buffer Interrupt Handler          */
                .long    PMPORT0_OB_Handler     /*     159 PMPORT1 Output Buffer Interrupt Handler         */
                .long    PMPORT1_IB_Handler     /*     160 PMPORT1 Input Buffer Interrupt Handler          */
                .long    PMPORT1_OB_Handler     /*     161 PMPORT1 Output Buffer Interrupt Handler         */
                .long    PMPORT2_IB_Handler     /*     162 PMPORT2 Input Buffer Interrupt Handler          */
                .long    PMPORT2_OB_Handler     /*     163 PMPORT2 Output Buffer Interrupt Handler         */
                .long    PMPORT3_IB_Handler     /*     164 PMPORT2 Input Buffer Interrupt Handler          */
                .long    PMPORT3_OB_Handler     /*     165 PMPORT2 Output Buffer Interrupt Handler         */
                .long    PORT80_Handler         /*     166 PORT80 Interrupt Handler                        */
                .long    PORT81_Handler         /*     167 PORT81 Interrupt Handler                        */ 
                .long    PECI_Handler           /*     168 PECI Interrupt Handler                          */
                .long    EFSAFOP2_Handler       /*     169 eSPI Flash Chanel SAF OP2 Interrupt Handler     */
                .long    0                      /*     170 Reserved                                        */
                .long    0                      /*     171 Reserved                                        */
                .long    0                      /*     172 Reserved                                        */
                .long    0                      /*     173 Reserved                                        */
                .long    0                      /*     174 Reserved                                        */
                .long    0                      /*     175 Reserved                                        */
                .long    0                      /*     176 Reserved                                        */
                .long    0                      /*     177 Reserved                                        */
                .long    0                      /*     178 Reserved                                        */
                .long    0                      /*     179 Reserved                                        */
                .long    SPIC_Handler           /*     180 SPIC Interrupt Handler                          */
                .long    HSP_Handler            /*     181 HSPI Interrupt Handler                          */
                .long    I2C0_Handler           /*     182 I2C0 Interrupt Handler                          */
                .long    I2C1_Handler           /*     183 I2C1 Interrupt Handler                          */
                .long    I2C2_Handler           /*     184 I2C2 Interrupt Handler                          */
                .long    I2C3_Handler           /*     185 I2C3 Interrupt Handler                          */
                .long    I2C4_Handler           /*     186 I2C4 Interrupt Handler                          */
                .long    I2C5_Handler           /*     187 I2C5 Interrupt Handler                          */
                .long    I2C6_Handler           /*     188 I2C6 Interrupt Handler                          */
                .long    I2C7_Handler           /*     189 I2C7 Interrupt Handler                          */
                .long    PS2_Handler            /*     190 PS2 Interrupt Handler                           */
                .long    UART_Handler           /*     191 UART Interrupt Handler                          */
                .long    TACHO0_Handler         /*     192 TACHO0 Interrupt Handler                        */
                .long    TACHO1_Handler         /*     193 TACHO1 Interrupt Handler                        */
                .long    TACHO2_Handler         /*     194 TACHO2 Interrupt Handler                        */
                .long    TACHO3_Handler         /*     195 TACHO3 Interrupt Handler                        */
                .long    TMR0_Handler           /*     196 TMR0 Interrupt Handler                          */ 
                .long    TMR1_Handler           /*     197 TMR1 Interrupt Handler                          */ 
                .long    TMR2_Handler           /*     198 TMR2 Interrupt Handler                          */ 
                .long    TMR3_Handler           /*     199 TMR3 Interrupt Handler                          */ 
                .long    TMR4_Handler           /*     200 TMR4 Interrupt Handler                          */ 
                .long    TMR5_Handler           /*     201 TMR5 Interrupt Handler                          */ 
                .long    SLWTMR0_Handler        /*     202 SLWTMR0 Interrupt Handler                       */
                .long    SLWTMR1_Handler        /*     203 SLWTMR1 Interrupt Handler                       */
                .long    RTMR_Handler           /*     204 RTMR Interrupt Handler                          */
                .long    RTC_Handler            /*     205 RTC Interrupt Handler                           */
                .long    I3C0_Handler           /*     206 I3C0 Interrupt Handler                          */    
                .long    I3C1_Handler           /*     207 I3C1 Interrupt Handler                          */
                .long    PWRBTN_Handler         /*     208 PWRBTN Interrupt Handler                        */
                .long    WDT_Handler            /*     209 WDT Interrupt Handler                           */
                .long    KBM_Handler            /*     210 KBM Interrupt Handler                           */
                .long    MSPI_Handler           /*     211 MSPI Interrupt Handler                          */
                .long    EMI0_Handler           /*     212 EMI0 Interrupt Handler                          */
                .long    EMI1_Handler           /*     213 EMI1 Interrupt Handler                          */
                .long    EMI2_Handler           /*     214 EMI2 Interrupt Handler                          */
                .long    EMI3_Handler           /*     215 EMI3 Interrupt Handler                          */
                .long    EMI4_Handler           /*     216 EMI4 Interrupt Handler                          */
                .long    EMI5_Handler           /*     217 EMI5 Interrupt Handler                          */
                .long    EMI6_Handler           /*     218 EMI6 Interrupt Handler                          */
                .long    EMI7_Handler           /*     219 EMI7 Interrupt Handler                          */
                .long    MBX_Handler            /*     220 MBX Interrupt Handler                           */
                .long    ADC_Handler            /*     221 ADC Interrupt Handler                           */
                .long    0                      /*     222 Reserved                                        */
                .long    0                      /*     223 Reserved                                        */
                .long    0                      /*     224 Reserved                                        */
                .long    0                      /*     225 Reserved                                        */
                .long    0                      /*     226 Reserved                                        */
                .long    0                      /*     227 Reserved                                        */
                .long    0                      /*     228 Reserved                                        */
                .long    0                      /*     229 Reserved                                        */
                .long    0                      /*     230 Reserved                                        */
                .long    0                      /*     231 Reserved                                        */
                .long    0                      /*     232 Reserved                                        */
                .long    0                      /*     233 Reserved                                        */
                .long    DMA_Handler            /*     234 DMA Interrupt Handler                           */
                .long    SHA2_Handler           /*     235 SHA2 Interrupt Handler                          */
                .long    SHA3_Handler           /*     236 SHA3 Interrupt Handler                          */
                .long    AES_Handler            /*     237 AES Interrupt Handler                           */
                .long    PKE_Handler            /*     238 PKE Interrupt Handler                           */
                .long    PUFOTP_Handler         /*     239 PUFOTP                                          */
                .long    0                      /*     240 Reserved                                        */

__Vectors_End:
                .equ        __Vectors_Size, __Vectors_End - __Vectors
                .size       __Vectors, . - __Vectors

/* Reset Handler */
                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
                /* Disable interrupts */
                cpsid i

                ldr     sp, =__StackTop
                ldr     r0, =__StackLimit
                msr     msplim,r0

                /* initialize data section */
                ldr     r0, =__etext
                ldr     r1, =__data_start__
                ldr     r2, =__data_end__
                subs    r2, r1

.L_crt_copy_data:
                subs    r2, #4
                ldr     r3, [r0, r2]
                str     r3, [r1, r2]
                bgt     .L_crt_copy_data

                /* initialize bss section */
                ldr     r0, =__bss_start__
                ldr     r1, =__bss_end__
                movs    r2, 0
                subs    r1, r0

.L_crt_clear_bss:
                subs    r1, #4
                str     r2, [r0, r1]
                bgt     .L_crt_clear_bss

                // SHCSR, System Handler Control and State Register
                ldr     r0, =0xE000ED24
                ldr     r1, =0x000F0000
                str     r1, [r0]

                /* enable interrupt */
                cpsie i

.L_System_Init:
                ldr     r0, =SystemInit
                blx     r0
                ldr     r0, =main
                bx      r0
                .fnend
                .size    Reset_Handler, . - Reset_Handler
            
/* Dummy Exception Handlers (infinite loops which can be modified) */
                .thumb_func
                .type    NMI_Handler, %function
                .weak    NMI_Handler
                .fnstart
NMI_Handler:
                b        .
                .fnend
                .size    NMI_Handler, . - NMI_Handler

                .thumb_func
                .type    HardFault_Handler, %function
                .weak    HardFault_Handler
                .fnstart
HardFault_Handler:
                b        .
                .fnend
                .size    HardFault_Handler, . - HardFault_Handler

                .thumb_func
                .type    MemManage_Handler, %function
                .weak    MemManage_Handler
                .fnstart
MemManage_Handler:
                b        .
                .fnend
                .size    MemManage_Handler, . - MemManage_Handler

                .thumb_func
                .type    BusFault_Handler, %function
                .weak    BusFault_Handler
                .fnstart
BusFault_Handler:
                nop
                nop
                nop
                b        .
                .fnend
                .size    BusFault_Handler, . - BusFault_Handler

                .thumb_func
                .type    UsageFault_Handler, %function
                .weak    UsageFault_Handler
                .fnstart
UsageFault_Handler:
                nop
                nop
                nop
                nop
                .fnend
                .size    UsageFault_Handler, . - UsageFault_Handler

                .thumb_func
                .type    SecureFault_Handler, %function
                .weak    SecureFault_Handler
                .fnstart
SecureFault_Handler:
                nop
                nop
                nop
                b        .
                .fnend
                .size    SecureFault_Handler, . - SecureFault_Handler

                .thumb_func
                .type    SVC_Handler, %function
                .weak    SVC_Handler
                .fnstart
SVC_Handler:
                b        .
                .fnend
                .size    SVC_Handler, . - SVC_Handler

                .thumb_func
                .type    DebugMon_Handler, %function
                .weak    DebugMon_Handler
                .fnstart
DebugMon_Handler:
                nop
                b        .
                .fnend
                .size    DebugMon_Handler, . - DebugMon_Handler

                .thumb_func
                .type    PendSV_Handler, %function
                .weak    PendSV_Handler
                .fnstart
PendSV_Handler:
                b        .
                .fnend
                .size    PendSV_Handler, . - PendSV_Handler

               .thumb_func
                .type    SysTick_Handler, %function
                .weak    SysTick_Handler
                .fnstart
SysTick_Handler:
                b        .
                .fnend
                .size    SysTick_Handler, . - SysTick_Handler

/* default handler */
                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                nop
                nop
                nop
                nop
                nop
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* macro */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm

/* Default exception/interrupt handler */
                Set_Default_Handler GPIO000_Handler
                Set_Default_Handler GPIO001_Handler
                Set_Default_Handler GPIO002_Handler
                Set_Default_Handler GPIO003_Handler
                Set_Default_Handler GPIO004_Handler
                Set_Default_Handler GPIO005_Handler
                Set_Default_Handler GPIO006_Handler
                Set_Default_Handler GPIO007_Handler
                Set_Default_Handler GPIO008_Handler
                Set_Default_Handler GPIO009_Handler
                Set_Default_Handler GPIO010_Handler
                Set_Default_Handler GPIO011_Handler
                Set_Default_Handler GPIO012_Handler
                Set_Default_Handler GPIO013_Handler
                Set_Default_Handler GPIO014_Handler
                Set_Default_Handler GPIO015_Handler
                Set_Default_Handler GPIO016_Handler
                Set_Default_Handler GPIO017_Handler
                Set_Default_Handler GPIO018_Handler
                Set_Default_Handler GPIO019_Handler
                Set_Default_Handler GPIO020_Handler
                Set_Default_Handler GPIO021_Handler
                Set_Default_Handler GPIO022_Handler
                Set_Default_Handler GPIO023_Handler
                Set_Default_Handler GPIO024_Handler
                Set_Default_Handler GPIO025_Handler
                Set_Default_Handler GPIO026_Handler
                Set_Default_Handler GPIO027_Handler
                Set_Default_Handler GPIO028_Handler
                Set_Default_Handler GPIO029_Handler
                Set_Default_Handler GPIO030_Handler
                Set_Default_Handler GPIO031_Handler
                Set_Default_Handler GPIO032_Handler
                Set_Default_Handler GPIO033_Handler
                Set_Default_Handler GPIO034_Handler
                Set_Default_Handler GPIO035_Handler
                Set_Default_Handler GPIO036_Handler
                Set_Default_Handler GPIO037_Handler
                Set_Default_Handler GPIO038_Handler
                Set_Default_Handler GPIO039_Handler
                Set_Default_Handler GPIO040_Handler
                Set_Default_Handler GPIO041_Handler
                Set_Default_Handler GPIO042_Handler
                Set_Default_Handler GPIO043_Handler
                Set_Default_Handler GPIO044_Handler
                Set_Default_Handler GPIO045_Handler
                Set_Default_Handler GPIO046_Handler
                Set_Default_Handler GPIO047_Handler
                Set_Default_Handler GPIO048_Handler
                Set_Default_Handler GPIO049_Handler
                Set_Default_Handler GPIO050_Handler
                Set_Default_Handler GPIO051_Handler
                Set_Default_Handler GPIO052_Handler
                Set_Default_Handler GPIO053_Handler
                Set_Default_Handler GPIO054_Handler
                Set_Default_Handler GPIO055_Handler
                Set_Default_Handler GPIO056_Handler
                Set_Default_Handler GPIO057_Handler
                Set_Default_Handler GPIO058_Handler
                Set_Default_Handler GPIO059_Handler
                Set_Default_Handler GPIO060_Handler
                Set_Default_Handler GPIO061_Handler
                Set_Default_Handler GPIO062_Handler
                Set_Default_Handler GPIO063_Handler
                Set_Default_Handler GPIO064_Handler
                Set_Default_Handler GPIO065_Handler
                Set_Default_Handler GPIO066_Handler
                Set_Default_Handler GPIO067_Handler
                Set_Default_Handler GPIO068_Handler
                Set_Default_Handler GPIO069_Handler
                Set_Default_Handler GPIO070_Handler
                Set_Default_Handler GPIO071_Handler
                Set_Default_Handler GPIO072_Handler
                Set_Default_Handler GPIO073_Handler
                Set_Default_Handler GPIO074_Handler
                Set_Default_Handler GPIO075_Handler
                Set_Default_Handler GPIO076_Handler
                Set_Default_Handler GPIO077_Handler
                Set_Default_Handler GPIO078_Handler
                Set_Default_Handler GPIO079_Handler
                Set_Default_Handler GPIO080_Handler
                Set_Default_Handler GPIO081_Handler
                Set_Default_Handler GPIO082_Handler
                Set_Default_Handler GPIO083_Handler
                Set_Default_Handler GPIO084_Handler
                Set_Default_Handler GPIO085_Handler
                Set_Default_Handler GPIO086_Handler
                Set_Default_Handler GPIO087_Handler
                Set_Default_Handler GPIO088_Handler
                Set_Default_Handler GPIO089_Handler
                Set_Default_Handler GPIO090_Handler
                Set_Default_Handler GPIO091_Handler
                Set_Default_Handler GPIO092_Handler
                Set_Default_Handler GPIO093_Handler
                Set_Default_Handler GPIO094_Handler
                Set_Default_Handler GPIO095_Handler
                Set_Default_Handler GPIO096_Handler
                Set_Default_Handler GPIO097_Handler
                Set_Default_Handler GPIO098_Handler
                Set_Default_Handler GPIO099_Handler
                Set_Default_Handler GPIO100_Handler
                Set_Default_Handler GPIO101_Handler
                Set_Default_Handler GPIO102_Handler
                Set_Default_Handler GPIO103_Handler
                Set_Default_Handler GPIO104_Handler
                Set_Default_Handler GPIO105_Handler
                Set_Default_Handler GPIO106_Handler
                Set_Default_Handler GPIO107_Handler
                Set_Default_Handler GPIO108_Handler
                Set_Default_Handler GPIO109_Handler
                Set_Default_Handler GPIO110_Handler
                Set_Default_Handler GPIO111_Handler
                Set_Default_Handler GPIO112_Handler
                Set_Default_Handler GPIO113_Handler
                Set_Default_Handler GPIO114_Handler
                Set_Default_Handler GPIO115_Handler
                Set_Default_Handler GPIO116_Handler
                Set_Default_Handler GPIO117_Handler
                Set_Default_Handler GPIO118_Handler
                Set_Default_Handler GPIO119_Handler
                Set_Default_Handler GPIO120_Handler
                Set_Default_Handler GPIO121_Handler
                Set_Default_Handler GPIO122_Handler
                Set_Default_Handler GPIO123_Handler
                Set_Default_Handler GPIO124_Handler
                Set_Default_Handler GPIO125_Handler
                Set_Default_Handler GPIO126_Handler
                Set_Default_Handler GPIO127_Handler
                Set_Default_Handler GPIO128_Handler
                Set_Default_Handler GPIO129_Handler
                Set_Default_Handler GPIO130_Handler
                Set_Default_Handler GPIO131_Handler
                Set_Default_Handler ERST_Handler
                Set_Default_Handler EPRCH_Handler
                Set_Default_Handler EVCHIDX61_Handler
                Set_Default_Handler EVCHIDX51_Handler 
                Set_Default_Handler EVCHIDX4A_Handler
                Set_Default_Handler EVCHIDX47_Handler
                Set_Default_Handler EVCHIDX44_Handler
                Set_Default_Handler EVCHIDX43_Handler
                Set_Default_Handler EVCHIDX42_Handler
                Set_Default_Handler EVCHIDX41_Handler
                Set_Default_Handler EVCHIDX7_Handler
                Set_Default_Handler EVCHIDX3_Handler
                Set_Default_Handler EVCHIDX2_Handler
                Set_Default_Handler EVCH_Handler
                Set_Default_Handler EOCHTX_Handler
                Set_Default_Handler EOCHRX_Handler
                Set_Default_Handler EOCHCFGEN_Handler
                Set_Default_Handler EFSAFSTR_Handler
                Set_Default_Handler EFSAFSERASE_Handler
                Set_Default_Handler EFMAFSTR_Handler
                Set_Default_Handler EFCHCHG_Handler
                Set_Default_Handler KBC_IB_Handler
                Set_Default_Handler KBC_OB_Handler
                Set_Default_Handler ACPI_IB_Handler
                Set_Default_Handler ACPI_OB_Handler
                Set_Default_Handler PMPORT0_IB_Handler
                Set_Default_Handler PMPORT0_OB_Handler
                Set_Default_Handler PMPORT1_IB_Handler
                Set_Default_Handler PMPORT1_OB_Handler
                Set_Default_Handler PMPORT2_IB_Handler
                Set_Default_Handler PMPORT2_OB_Handler
                Set_Default_Handler PMPORT3_IB_Handler
                Set_Default_Handler PMPORT3_OB_Handler
                Set_Default_Handler PORT80_Handler
                Set_Default_Handler PORT81_Handler
                Set_Default_Handler PECI_Handler
                Set_Default_Handler EFSAFOP2_Handler
                Set_Default_Handler SPIC_Handler
                Set_Default_Handler HSP_Handler
                Set_Default_Handler I2C0_Handler
                Set_Default_Handler I2C1_Handler
                Set_Default_Handler I2C2_Handler
                Set_Default_Handler I2C3_Handler
                Set_Default_Handler I2C4_Handler
                Set_Default_Handler I2C5_Handler
                Set_Default_Handler I2C6_Handler
                Set_Default_Handler I2C7_Handler
                Set_Default_Handler PS2_Handler
                Set_Default_Handler UART_Handler
                Set_Default_Handler TACHO0_Handler
                Set_Default_Handler TACHO1_Handler
                Set_Default_Handler TACHO2_Handler
                Set_Default_Handler TACHO3_Handler
                Set_Default_Handler TMR0_Handler
                Set_Default_Handler TMR1_Handler
                Set_Default_Handler TMR2_Handler
                Set_Default_Handler TMR3_Handler
                Set_Default_Handler TMR4_Handler
                Set_Default_Handler TMR5_Handler
                Set_Default_Handler SLWTMR0_Handler
                Set_Default_Handler SLWTMR1_Handler
                Set_Default_Handler RTMR_Handler
                Set_Default_Handler RTC_Handler
                Set_Default_Handler I3C0_Handler
                Set_Default_Handler I3C1_Handler
                Set_Default_Handler PWRBTN_Handler
                Set_Default_Handler WDT_Handler
                Set_Default_Handler KBM_Handler
                Set_Default_Handler MSPI_Handler
                Set_Default_Handler EMI0_Handler
                Set_Default_Handler EMI1_Handler
                Set_Default_Handler EMI2_Handler
                Set_Default_Handler EMI3_Handler
                Set_Default_Handler EMI4_Handler
                Set_Default_Handler EMI5_Handler
                Set_Default_Handler EMI6_Handler
                Set_Default_Handler EMI7_Handler
                Set_Default_Handler MBX_Handler
                Set_Default_Handler ADC_Handler
                Set_Default_Handler DMA_Handler
                Set_Default_Handler SHA2_Handler
                Set_Default_Handler SHA3_Handler
                Set_Default_Handler AES_Handler
                Set_Default_Handler PKE_Handler
                Set_Default_Handler PUFOTP_Handler

