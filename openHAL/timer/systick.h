#ifndef OHAL_SYSTICK_H
#define OHAL_SYSTICK_H

#include <stddef.h>
#include <openHAL/timer/timer.h>

/**
 * @file systick.h
 * @brief Configuration for the Cortex-M SysTick timer driver.
 */

/**
 * @brief Available SysTick clock sources.
 */
typedef enum {
    OHAL_SYSTICK_CLKSRC_EXT,
    OHAL_SYSTICK_CLKSRC_SYSCLK,
} ohal_SysTick_ClkSrc;

/**
 * @brief Enable or disable the SysTick interrupt generation.
 */
typedef enum {
    OHAL_SYSTICK_TICKINT_DISABLED,
    OHAL_SYSTICK_TICKINT_ENABLED,
} ohal_SysTick_TickInt;

/**
 * @brief SysTick configuration parameters.
 */
typedef struct {
    size_t cyclesPerTick;
    ohal_SysTick_ClkSrc clkSrc;
    ohal_SysTick_TickInt tickInt;
} ohal_SysTick_Cfg;

/** Driver instance for the Cortex-M SysTick timer. */
extern ohal_TimerDriver g_sysTickDriver;

#endif /* OHAL_SYSTICK_H */
