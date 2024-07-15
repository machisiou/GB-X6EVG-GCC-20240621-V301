/*******************************************************************************
 * @file     system_RTS5911.c
 * @brief    CMSIS Device System Source File for RTS5911 Device
 * @version  V1.00
 * @date     30. March 2023
 ******************************************************************************/
/* Copyright (c) 2015 - 2016 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#if (__ARM_FEATURE_CMSE == 3U)
  #include "partition_RLE1199.h"
#endif
#include "chip/rts5911/RTS5911.h"
#include "chip/rts5911/system_RTS5911.h"
extern void *__Vectors;                   /* see startup file */
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define SYS_CLK_RC25M_DIV1      (25000000UL)        /* From Internal RC25M DIV1 frequency */
#define SYS_CLK_RC25M_DIV2      (12500000UL)        /* From Internal RC25M DIV2 frequency */
#define SYS_CLK_PLL_DIV1        (100000000UL)       /* From PLL DIV1 frequency */
#define SYS_CLK_PLL_DIV2        (50000000UL)        /* From PLL DIV2 frequency */

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYS_CLK_RC25M_DIV1;  /* System Core Clock Frequency */

void SystemCoreClockUpdate (void)
{
    if (SYSTEM->SYSCLK_b.CLKSRC) {
        SystemCoreClock = SYSTEM->SYSCLK_b.DIV ? SYS_CLK_PLL_DIV2 : SYS_CLK_PLL_DIV1;
    } else {
        SystemCoreClock = SYSTEM->SYSCLK_b.DIV ? SYS_CLK_RC25M_DIV2 : SYS_CLK_RC25M_DIV1;
    }
}

void SystemInit (void)
{
  SCB->VTOR = (uint32_t) &__Vectors;

#if defined (__FPU_USED) && (__FPU_USED == 1)
  SCB->CPACR |= ((3U << 10*2) |           /* set CP10 Full Access */
                 (3U << 11*2)  );         /* set CP11 Full Access */
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
  SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  TZ_SAU_Setup();
#endif
    
  SystemCoreClockUpdate();
}
