#include <openHAL/flash/flash.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Flash_Init(ohal_Flash *flashDev)
{
    if (!flashDev || !flashDev->driver || !flashDev->driver->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return flashDev->driver->Init(flashDev);
}

inline ohal_Error ohal_Flash_Deinit(ohal_Flash *flashDev)
{
    if (!flashDev || !flashDev->driver || !flashDev->driver->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return flashDev->driver->Deinit(flashDev);
}

inline ohal_Error ohal_Flash_Write(ohal_Flash *flashDev, size_t addr, u8 *data,
                                  size_t dataSz)
{
    if (!flashDev || !flashDev->driver || !flashDev->driver->Write || !data) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return flashDev->driver->Write(flashDev, addr, data, dataSz);
}

inline ohal_Error ohal_Flash_Erase(ohal_Flash *flashDev, size_t addr,
                                  size_t dataSz)
{
    if (!flashDev || !flashDev->driver || !flashDev->driver->Erase) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return flashDev->driver->Erase(flashDev, addr, dataSz);
}

inline ohal_Error ohal_Flash_Cmd(ohal_Flash *flashDev, size_t cmd, void *args)
{
    if (!flashDev || !flashDev->driver || !flashDev->driver->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return flashDev->driver->Cmd(flashDev, cmd, args);
}
