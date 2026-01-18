#include <openHAL/clock/clock.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Clock_Init(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->driver->Init(clkDev);
}

inline ohal_Error ohal_Clock_Deinit(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->driver->Deinit(clkDev);
}

inline ohal_Error ohal_Clock_Enable(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->Enable) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->driver->Enable(clkDev);
}

inline ohal_Error ohal_Clock_Disable(ohal_Clock *clkDev)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->Disable) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->driver->Disable(clkDev);
}

inline ohal_Error ohal_Clock_GetRate(ohal_Clock *clkDev, size_t *rateOut)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->GetRate ||
        !rateOut) 
    {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
    }

    return clkDev->driver->GetRate(clkDev, rateOut);
}

inline ohal_Error ohal_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args)
{
    if (!clkDev || !clkDev->driver || !clkDev->driver->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return clkDev->driver->Cmd(clkDev, cmd, args);
}
