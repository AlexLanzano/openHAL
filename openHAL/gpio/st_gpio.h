#ifndef OHAL_STGPIO_H
#define OHAL_STGPIO_H

#include <openHAL/types.h>
#include <openHAL/gpio/gpio.h>

/**
 * @file st_gpio.h
 * @brief STM32 GPIO driver configuration types.
 */

/**
 * @brief STM32 GPIO port identifiers.
 */
typedef enum {
    OHAL_STGPIO_PORT_A,
    OHAL_STGPIO_PORT_B,
    OHAL_STGPIO_PORT_C,
    OHAL_STGPIO_PORT_D,
    OHAL_STGPIO_PORT_E,
    OHAL_STGPIO_PORT_F,
    OHAL_STGPIO_PORT_G,
    OHAL_STGPIO_PORT_H,
} ohal_StGpio_Port;

/**
 * @brief GPIO direction and function modes.
 */
typedef enum {
    OHAL_STGPIO_MODE_IN,
    OHAL_STGPIO_MODE_OUT,
    OHAL_STGPIO_MODE_ALTFN,
    OHAL_STGPIO_MODE_ANALOG,
} ohal_StGpio_Mode;

/**
 * @brief Output driver type.
 */
typedef enum {
    OHAL_STGPIO_OUTTYPE_PUSHPULL,
    OHAL_STGPIO_OUTTYPE_OPENDRAIN,
} ohal_StGpio_OutType;

/**
 * @brief Output speed settings.
 */
typedef enum {
    OHAL_STGPIO_SPEED_LOW,
    OHAL_STGPIO_SPEED_MEDIUM,
    OHAL_STGPIO_SPEED_FAST,
    OHAL_STGPIO_SPEED_HIGH,
} ohal_StGpio_Speed;

/**
 * @brief Pull resistor configuration.
 */
typedef enum {
    OHAL_STGPIO_PULL_NONE,
    OHAL_STGPIO_PULL_UP,
    OHAL_STGPIO_PULL_DOWN,
} ohal_StGpio_Pull;

/**
 * @brief Per-pin STM32 GPIO configuration.
 */
typedef struct {
    ohal_StGpio_Port port;
    u8 pin;
    ohal_StGpio_Mode mode;
    ohal_StGpio_OutType outType;
    ohal_StGpio_Speed speed;
    ohal_StGpio_Pull pull;
    u8 altFn;
} ohal_StGpio_Cfg;

/** Driver instance for STM32 GPIO. */
extern ohal_GpioDriver g_stGpioDriver;

#endif /* OHAL_STGPIO_H */
