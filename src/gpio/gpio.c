#include <openHAL/gpio/gpio.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Gpio_Init(ohal_Gpio *gpioDev)
{
    if (!gpioDev || !gpioDev->ops || !gpioDev->ops->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->ops->Init(gpioDev);
}

inline ohal_Error ohal_Gpio_Deinit(ohal_Gpio *gpioDev)
{
    if (!gpioDev || !gpioDev->ops || !gpioDev->ops->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->ops->Deinit(gpioDev);
    
}

inline ohal_Error ohal_Gpio_Get(ohal_Gpio *gpioDev, size_t pin, size_t *value)
{
    if (!gpioDev || !gpioDev->ops || !gpioDev->ops->Init || !value) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->ops->Get(gpioDev, pin, value);

}

inline ohal_Error ohal_Gpio_Set(ohal_Gpio *gpioDev, size_t pin, size_t value)
{
    if (!gpioDev || !gpioDev->ops || !gpioDev->ops->Set) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->ops->Set(gpioDev, pin, value);
}

inline ohal_Error ohal_Gpio_Cmd(ohal_Gpio *gpioDev, size_t cmd, void *args)
{
    if (!gpioDev || !gpioDev->ops || !gpioDev->ops->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return gpioDev->ops->Cmd(gpioDev, cmd, args);
}
