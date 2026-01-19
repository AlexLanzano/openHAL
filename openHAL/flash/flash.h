#ifndef OHAL_FLASH_H
#define OHAL_FLASH_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

typedef struct ohal_Flash ohal_Flash;

typedef struct {
    ohal_Error (*Init)(ohal_Flash *flashDev);
    ohal_Error (*Deinit)(ohal_Flash *flashDev);
    ohal_Error (*Write)(ohal_Flash *flashDev, size_t addr, u8 *data, size_t dataSz);
    ohal_Error (*Erase)(ohal_Flash *flashDev, size_t addr, size_t dataSz);
    ohal_Error (*Cmd)(ohal_Flash *flashDev, size_t cmd, void *args);
} ohal_FlashDriver;

struct ohal_Flash {
    ohal_Device dev;
    ohal_FlashDriver *driver;
    void *cfg;
};

ohal_Error ohal_Flash_Init(ohal_Flash *flashDev);
ohal_Error ohal_Flash_Deinit(ohal_Flash *flashDev);
ohal_Error ohal_Flash_Write(ohal_Flash *flashDev, size_t addr, u8 *data, size_t dataSz);
ohal_Error ohal_Flash_Erase(ohal_Flash *flashDev, size_t addr, size_t dataSz);
ohal_Error ohal_Flash_Cmd(ohal_Flash *flashDev, size_t cmd, void *args);

#endif /* OHAL_FLASH_H */
