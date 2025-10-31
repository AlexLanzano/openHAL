#include <openHAL/error.h>
#include <openHAL/clock/st_hal_clock.c>

static ohal_Error St_Clock_Init(ohal_Clock *clkDev)
{

    int ret; 
    ohal_St_ClockCfg *clkCfg = (ohal_St_ClockCfg *)clkDev->cfg;


    return OHAL_SUCCESS;
}

static ohal_Error St_Clock_Deinit(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error St_Clock_Enable(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error St_Clock_Disable(ohal_Clock *clkDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error St_Clock_GetRate(ohal_Clock *clkDev, size_t *rateOut)
{

    return OHAL_SUCCESS;
}

static ohal_Error St_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args)
{
    return OHAL_ENOTSUPP;
}

ohal_ClockOps g_stClockOps = {
    .Init = St_Clock_Init,
    .Deinit = St_Clock_Deinit,
    .Enable = St_Clock_Enable,
    .Disable = St_Clock_Disable,
    .GetRate = St_Clock_GetRate,
    .Cmd = St_Clock_Cmd,
};
