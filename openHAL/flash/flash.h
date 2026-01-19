#ifndef OHAL_FLASH_H
#define OHAL_FLASH_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

/**
 * @file flash.h
 * @brief Generic flash abstraction and driver interface.
 */

typedef struct ohal_Flash ohal_Flash;

/**
 * @brief Driver vtable for flash devices.
 */
typedef struct {
    /** Bring the flash peripheral into a usable state. */
    ohal_Error (*Init)(ohal_Flash *flashDev);
    /** Release any resources owned by the flash driver. */
    ohal_Error (*Deinit)(ohal_Flash *flashDev);
    /** Program a region of flash starting at @p addr. */
    ohal_Error (*Write)(ohal_Flash *flashDev, size_t addr, u8 *data, size_t dataSz);
    /** Erase a flash range starting at @p addr. */
    ohal_Error (*Erase)(ohal_Flash *flashDev, size_t addr, size_t dataSz);
    /** Issue a driver-specific command. */
    ohal_Error (*Cmd)(ohal_Flash *flashDev, size_t cmd, void *args);
} ohal_FlashDriver;

/**
 * @brief Flash device instance tying configuration to a driver implementation.
 */
struct ohal_Flash {
    ohal_Device dev;
    ohal_FlashDriver *driver;
    void *cfg;
};

/**
 * @brief Initialize a flash device and its driver.
 *
 * @param flashDev Flash instance to initialize.
 *
 * @retval OHAL_SUCCESS Driver-specific init completed.
 * @retval OHAL_EINVAL  Null pointer or missing driver callbacks.
 */
ohal_Error ohal_Flash_Init(ohal_Flash *flashDev);
/**
 * @brief Deinitialize a flash device.
 *
 * @param flashDev Flash instance to deinitialize.
 *
 * @retval OHAL_SUCCESS Driver-specific deinit completed.
 * @retval OHAL_EINVAL  Null pointer or missing driver callbacks.
 */
ohal_Error ohal_Flash_Deinit(ohal_Flash *flashDev);
/**
 * @brief Write data into flash.
 *
 * @param flashDev Flash instance to program.
 * @param addr     Byte address in flash to start writing.
 * @param data     Buffer containing data to write.
 * @param dataSz   Number of bytes to write.
 *
 * @retval OHAL_SUCCESS Write accepted or completed.
 * @retval OHAL_EINVAL  Null pointer, missing callbacks, or bad arguments.
 */
ohal_Error ohal_Flash_Write(ohal_Flash *flashDev, size_t addr, u8 *data, size_t dataSz);
/**
 * @brief Erase a region of flash.
 *
 * @param flashDev Flash instance to erase.
 * @param addr     Byte address in flash where erasure starts.
 * @param dataSz   Number of bytes (or sector-aligned size) to erase.
 *
 * @retval OHAL_SUCCESS Erase accepted or completed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Flash_Erase(ohal_Flash *flashDev, size_t addr, size_t dataSz);
/**
 * @brief Send a driver-specific command to the flash device.
 *
 * @param flashDev Flash instance to command.
 * @param cmd      Driver-defined command selector.
 * @param args     Optional command argument payload.
 *
 * @retval OHAL_SUCCESS Command accepted and executed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Flash_Cmd(ohal_Flash *flashDev, size_t cmd, void *args);

#endif /* OHAL_FLASH_H */
