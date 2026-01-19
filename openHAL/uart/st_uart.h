#ifndef OHAL_ST_UART_H
#define OHAL_ST_UART_H

#include <openHAL/types.h>
#include <openHAL/clock/clock.h>
#include <openHAL/uart/uart.h>
#include <stddef.h>

/**
 * @file st_uart.h
 * @brief STM32 UART driver configuration.
 */

/**
 * @brief STM32 UART configuration parameters.
 */
typedef struct ohal_StUart_Cfg {
    u32 baud;
    ohal_Clock *sysClk;
} ohal_StUart_Cfg;

/** Driver instance for STM32 UART peripheral. */
extern ohal_UartDriver g_stUartDriver;

#endif /* OHAL_ST_UART_H */
