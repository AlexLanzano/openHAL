#ifndef OHAL_ST_RCC_H
#define OHAL_ST_RCC_H

#include <openHAL/types.h>
#include <openHAL/clock/clock.h>
#include <stddef.h>

typedef enum {
    OHAL_ST_RCC_SYSCLK_SRC_MSI,
    OHAL_ST_RCC_SYSCLK_SRC_HSI16,
    OHAL_ST_RCC_SYSCLK_SRC_HSE,
    OHAL_ST_RCC_SYSCLK_SRC_PLL,
} ohal_StRcc_SysClockSrc;

typedef enum {
    OHAL_ST_RCC_PLLCLK_SRC_NONE,
    OHAL_ST_RCC_PLLCLK_SRC_MSI,
    OHAL_ST_RCC_PLLCLK_SRC_HSI16,
    OHAL_ST_RCC_PLLCLK_SRC_HSE,
} ohal_StRcc_PllClockSrc;

typedef enum ohal_StRcc_PeriphClk {
    OHAL_ST_RCC_PERIPH_GPIOA,
    OHAL_ST_RCC_PERIPH_GPIOB,
    OHAL_ST_RCC_PERIPH_LPUART1,
} ohal_StRcc_PeriphClk;

typedef struct ohal_StRcc_PllClkCfg {
    ohal_StRcc_PllClockSrc clkSrc;
    u8 r;
    u8 q;
    u8 p;
    u8 n;
    u8 m;
} ohal_StRcc_PllClkCfg;

typedef struct ohal_StRcc_MsiClkCfg {
    size_t freq;
} ohal_StRcc_MsiClkCfg;

typedef struct ohal_StRcc_Cfg {
    ohal_StRcc_SysClockSrc sysClkSrc;

    union {
        ohal_StRcc_PllClkCfg pll;
        ohal_StRcc_MsiClkCfg msi;
    } sysClkCfg;

    ohal_StRcc_PeriphClk *periphClkEn;
    u8 periphClkEnCount;
} ohal_StRcc_Cfg;

extern ohal_ClockDriver g_stRccDriver;

#endif /* OHAL_ST_RCC_H */
