#include <openHAL/error.h>
#include <openHAL/clock/st_hal_clock.c>

static ohal_Error StHal_Clock_Init(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error StHal_Clock_Deinit(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error StHal_Clock_Enable(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error StHal_Clock_Disable(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error StHal_Clock_GetRate(ohal_Clock *clkDev, size_t *rateOut)
{

    return OHAL_SUCCESS;
}

static ohal_Error StHal_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args)
{
    return OHAL_ENOTSUPP;
}
