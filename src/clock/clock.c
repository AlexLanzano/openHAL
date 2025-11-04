#include <openHAL/clock/clock.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Clock_Init(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->ops->Init(clkDev);
}

inline ohal_Error ohal_Clock_Deinit(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->ops->Deinit(clkDev);
}

inline ohal_Error ohal_Clock_Enable(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->Enable) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->ops->Enable(clkDev);
}

inline ohal_Error ohal_Clock_Disable(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->Disable) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->ops->Disable(clkDev);
}

inline ohal_Error ohal_Clock_GetRate(ohal_Clock *clkDev, size_t *rateOut)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->GetRate ||
        !rateOut) 
    {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
    }

    return clkDev->ops->GetRate(clkDev, rateOut);
}

inline ohal_Error ohal_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args)
{
    if (!clkDev || !clkDev->ops || !clkDev->ops->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->ops->Cmd(clkDev, cmd, args);
}
