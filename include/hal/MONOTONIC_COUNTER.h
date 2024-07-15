#ifndef __MONOTONIC_COUNTER_H__
#define __MONOTONIC_COUNTER_H__

#include <stdint.h>

extern uint32_t Monotonic_ReadCounter(uint32_t SelCnt);
extern void Monotonic_WriteCounter(uint32_t SelCnt);

#endif
