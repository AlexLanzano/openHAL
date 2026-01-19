#include <openHAL/platform/st/stm32wb55xx.h>
#include "stm32wb55xx_nucleo.h"

ohal_StRcc_PeriphClk periphClkEn[] =
{
    OHAL_ST_RCC_PERIPH_GPIOA,
    OHAL_ST_RCC_PERIPH_GPIOB,
    OHAL_ST_RCC_PERIPH_LPUART1,
};

ohal_StRcc_Cfg rccCfg =
{
    .sysClkSrc = OHAL_ST_RCC_SYSCLK_SRC_PLL,
    .sysClkCfg.pll =
    {
        .clkSrc = OHAL_ST_RCC_PLLCLK_SRC_MSI,
        /* 64 MHz */
        .n = 32,
        .m = 0,
        .r = 1,
        .q = 0,
        .p = 0,
    },
    .periphClkEn = periphClkEn,
    .periphClkEnCount = sizeof(periphClkEn),
};

ohal_Clock rcc = {
    OHAL_STM32WB55XX_RCC_DEVICE,
    .cfg = &rccCfg,
};

ohal_StGpio_Cfg gpioCfg[] = {
    [LED_PIN] = { /* LED */
        .port = OHAL_STGPIO_PORT_B,
        .pin = 5,
        .mode = OHAL_STGPIO_MODE_OUT,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_LOW,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 0,
    },
    [LPUART1_TX_PIN] = { /* LPUART1 TX */
        .port = OHAL_STGPIO_PORT_A,
        .pin = 2,
        .mode = OHAL_STGPIO_MODE_ALTFN,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_FAST,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 8,
    },
    [LPUART1_RX_PIN] = { /* LPUART1 RX */
        .port = OHAL_STGPIO_PORT_A,
        .pin = 3,
        .mode = OHAL_STGPIO_MODE_ALTFN,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_FAST,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 8,
    },
};

ohal_Gpio gpio = {
    OHAL_STM32WB55XX_GPIO_DEVICE,
    .pinCfg = &gpioCfg,
    .pinCount = sizeof(gpioCfg) / sizeof(ohal_StGpio_Cfg),
};

ohal_SysTick_Cfg sysTickCfg = {
    .cyclesPerTick = 64000000 / 1000,
    .clkSrc = OHAL_SYSTICK_CLKSRC_SYSCLK,
    .tickInt = OHAL_SYSTICK_TICKINT_ENABLED,
};

ohal_Timer sysTickTimer = {
    OHAL_CORTEX_M_SYSTICK_DEVICE,
    .cfg = &sysTickCfg,
};

ohal_StUart_Cfg lpuart1Cfg = {
    .baud = 115200,
    .sysClk = &rcc,
};

ohal_Uart lpuart1 = {
    OHAL_STM32WB55XX_LPUART1_DEVICE,
    .cfg = &lpuart1Cfg,
};

ohal_Flash flash = {
    OHAL_STM32WB55XX_FLASH_DEVICE,
};
