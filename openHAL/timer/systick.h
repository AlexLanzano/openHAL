#ifndef OHAL_SYSTICK_H
#define OHAL_SYSTICK_H

#include <stddef.h>
#include <openHAL/timer/timer.h>

typedef enum {
    OHAL_SYSTICK_CLKSRC_EXT,
    OHAL_SYSTICK_CLKSRC_SYSCLK,
} ohal_SysTick_ClkSrc;

typedef enum {
    OHAL_SYSTICK_TICKINT_DISABLED,
    OHAL_SYSTICK_TICKINT_ENABLED,
} ohal_SysTick_TickInt;

typedef struct {
    size_t cyclesPerTick;
    ohal_SysTick_ClkSrc clkSrc;
    ohal_SysTick_TickInt tickInt;
} ohal_SysTick_Cfg;

#endif /* OHAL_SYSTICK_H */
