#ifndef OHAL_GPIO_H
#define OHAL_GPIO_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

/**
 * @file gpio.h
 * @brief Generic GPIO abstraction and driver interface.
 */

typedef struct ohal_Gpio ohal_Gpio;

/**
 * @brief Driver vtable for GPIO devices.
 */
typedef struct {
    /** Initialize GPIO hardware and configured pins. */
    ohal_Error (*Init)(ohal_Gpio *gpioDev); 
    /** Deinitialize GPIO hardware. */
    ohal_Error (*Deinit)(ohal_Gpio *gpioDev); 
    /** Read a pin value. */
    ohal_Error (*Get)(ohal_Gpio *gpioDev, size_t pin, size_t *value); 
    /** Write a pin value. */
    ohal_Error (*Set)(ohal_Gpio *gpioDev, size_t pin, size_t value); 
    /** Issue driver-specific commands. */
    ohal_Error (*Cmd)(ohal_Gpio *gpioDev, size_t cmd, void *args);
} ohal_GpioDriver;

/**
 * @brief GPIO device instance containing driver, configuration, and pin table.
 */
struct ohal_Gpio {
    ohal_Device dev;
    ohal_GpioDriver *driver;
    void *pinCfg;
    size_t pinCount;
};

/**
 * @brief Initialize a GPIO device and its pins.
 *
 * @param gpioDev GPIO instance to initialize.
 *
 * @retval OHAL_SUCCESS Driver-specific init completed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Gpio_Init(ohal_Gpio *gpioDev);
/**
 * @brief Deinitialize a GPIO device.
 *
 * @param gpioDev GPIO instance to deinitialize.
 *
 * @retval OHAL_SUCCESS Driver-specific deinit completed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Gpio_Deinit(ohal_Gpio *gpioDev);
/**
 * @brief Read the state of a pin.
 *
 * @param gpioDev GPIO instance containing the pin.
 * @param pin     Pin index into the configured pin table.
 * @param value   Storage for the sampled pin value.
 *
 * @retval OHAL_SUCCESS Pin value stored in @p value.
 * @retval OHAL_EINVAL  Null pointer, missing callbacks, or bad pin.
 */
ohal_Error ohal_Gpio_Get(ohal_Gpio *gpioDev, size_t pin, size_t *value);
/**
 * @brief Set the state of a pin.
 *
 * @param gpioDev GPIO instance containing the pin.
 * @param pin     Pin index into the configured pin table.
 * @param value   Output value to drive (typically 0 or 1).
 *
 * @retval OHAL_SUCCESS Pin updated.
 * @retval OHAL_EINVAL  Null pointer, missing callbacks, or bad pin.
 */
ohal_Error ohal_Gpio_Set(ohal_Gpio *gpioDev, size_t pin, size_t value);
/**
 * @brief Send a driver-specific command to the GPIO device.
 *
 * @param gpioDev GPIO instance to command.
 * @param cmd     Driver-defined command selector.
 * @param args    Optional command argument payload.
 *
 * @retval OHAL_SUCCESS Command accepted and executed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Gpio_Cmd(ohal_Gpio *gpioDev, size_t cmd, void *args);

#endif /* OHAL_GPIO_H */
