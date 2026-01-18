#include <openHAL/gpio/gpio.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Gpio_Init(ohal_Gpio *gpioDev)
{
    if (!gpioDev || !gpioDev->driver || !gpioDev->driver->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->driver->Init(gpioDev);
}

inline ohal_Error ohal_Gpio_Deinit(ohal_Gpio *gpioDev)
{
    if (!gpioDev || !gpioDev->driver || !gpioDev->driver->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->driver->Deinit(gpioDev);
    
}

inline ohal_Error ohal_Gpio_Get(ohal_Gpio *gpioDev, size_t pin, size_t *value)
{
    if (!gpioDev || !gpioDev->driver || !gpioDev->driver->Init || !value) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->driver->Get(gpioDev, pin, value);

}

inline ohal_Error ohal_Gpio_Set(ohal_Gpio *gpioDev, size_t pin, size_t value)
{
    if (!gpioDev || !gpioDev->driver || !gpioDev->driver->Set) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->driver->Set(gpioDev, pin, value);
}

inline ohal_Error ohal_Gpio_Cmd(ohal_Gpio *gpioDev, size_t cmd, void *args)
{
    if (!gpioDev || !gpioDev->driver || !gpioDev->driver->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->driver->Cmd(gpioDev, cmd, args);
}
