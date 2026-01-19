#ifndef OHAL_STM32WB55XX_H
#define OHAL_STM32WB55XX_H

#include <openHAL/clock/st_rcc.h>
#include <openHAL/gpio/st_gpio.h>
#include <openHAL/timer/systick.h>
#include <openHAL/uart/st_uart.h>
#include <openHAL/flash/st_flash.h>

#define OHAL_STM32WB55XX_LPUART1_DEVICE \
    .dev = {                            \
        .name = "lpuart1",              \
        .reg = {                        \
            .base = 0x40008000,         \
            .size = 0x400,              \
        },                              \
    },                                  \
    .driver = &g_stUartDriver

#define OHAL_STM32WB55XX_GPIO_DEVICE \
    .dev = {                        \
        .name = "gpio",             \
        .reg = {                    \
            .base = 0x48000000,     \
            .size = 0x2000,         \
        },                          \
    },                              \
    .driver = &g_stGpioDriver

#define OHAL_STM32WB55XX_RCC_DEVICE \
    .dev = {                        \
        .name = "rcc",              \
        .reg = {                    \
            .base = 0x58000000,     \
            .size = 0x400,          \
        },                          \
    },                              \
    .driver = &g_stRccDriver

#define OHAL_STM32WB55XX_FLASH_DEVICE \
    .dev = {                        \
        .name = "flash",            \
        .reg = {                    \
            .base = 0x58004000,     \
            .size = 0x400,          \
        },                          \
    },                              \
    .driver = &g_stFlashDriver

#define OHAL_CORTEX_M_SYSTICK_DEVICE \
    .dev = {                        \
        .name = "systick",          \
        .reg = {                    \
            .base = 0xE000E010,     \
            .size = 0x400,          \
        },                          \
    },                              \
    .driver = &g_sysTickDriver
    
#endif /* OHAL_STM32WB55XX_H */
