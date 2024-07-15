/**
 * @file interrupt.h
 * @author Jim Lai (jim.lai@realtek.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#if defined(__RTS5911__)
#include "chip/rts5911/nvic.h"
#else
#error Unspecified Realtek CPU Project !
#endif