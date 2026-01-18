#ifndef OHAL_ST_CLOCK_H
#define OHAL_ST_CLOCK_H

#include <openHAL/types.h>
#include <openHAL/clock/clock.h>
#include <stddef.h>

typedef enum {
    OHAL_ST_CLOCK_SYSCLK_SRC_MSI,
    OHAL_ST_CLOCK_SYSCLK_SRC_HSI16,
    OHAL_ST_CLOCK_SYSCLK_SRC_HSE,
    OHAL_ST_CLOCK_SYSCLK_SRC_PLL,
} ohal_StClock_SysClockSrc;

typedef enum {
    OHAL_ST_CLOCK_PLLCLK_SRC_NONE,
    OHAL_ST_CLOCK_PLLCLK_SRC_MSI,
    OHAL_ST_CLOCK_PLLCLK_SRC_HSI16,
    OHAL_ST_CLOCK_PLLCLK_SRC_HSE,
} ohal_StClock_PllClockSrc;

typedef enum ohal_StClock_PeriphClk {
    OHAL_ST_CLOCK_PERIPH_GPIOA,
    OHAL_ST_CLOCK_PERIPH_GPIOB,
    OHAL_ST_CLOCK_PERIPH_LPUART1,
} ohal_StClock_PeriphClk;

typedef struct ohal_StClock_PllClkCfg {
    ohal_StClock_PllClockSrc clkSrc;
    u8 r;
    u8 q;
    u8 p;
    u8 n;
    u8 m;
} ohal_StClock_PllClkCfg;

typedef struct ohal_StClock_MsiClkCfg {
    size_t freq;
} ohal_StClock_MsiClkCfg;

typedef struct ohal_StClock_Cfg {
    ohal_StClock_SysClockSrc sysClkSrc;

    union {
        ohal_StClock_PllClkCfg pll;
        ohal_StClock_MsiClkCfg msi;
    } sysClkCfg;

    ohal_StClock_PeriphClk *periphClkEn;
    u8 periphClkEnCount;
} ohal_StClock_Cfg;

extern ohal_ClockDriver g_stClockDriver;

#endif /* OHAL_ST_CLOCK_H */
