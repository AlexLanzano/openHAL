#include <openHAL/error.h>
#include <openHAL/bitops.h>
#include <openHAL/timer/timer.h>
#include <openHAL/timer/systick.h>

#define SYSTICK_CSR_REG 0x00
#define SYSTICK_CSR_ENABLE OHAL_MASK(0)
#define SYSTICK_CSR_TICKINT OHAL_MASK(1)
#define SYSTICK_CSR_CLKSOURCE OHAL_MASK(2)
#define SYSTICK_CSR_COUNTFLAG OHAL_MASK(16)

#define SYSTICK_RVR_REG 0x04
#define SYSTICK_RVR_RELOAD OHAL_MASK_RANGE(23, 0)

static ohal_Error SysTick_Init(ohal_Timer *timerDev)
{
    ohal_Error err;
    ohal_SysTick_Cfg *cfg;
    ohal_Reg *reg = &timerDev->dev.reg;
    
    if (!timerDev || !timerDev->cfg) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_SysTick_Cfg *)timerDev->cfg;

    err = ohal_Reg_Update(reg, SYSTICK_CSR_REG,
                          SYSTICK_CSR_CLKSOURCE | SYSTICK_CSR_TICKINT,
                          ohal_SetBits(SYSTICK_CSR_CLKSOURCE, cfg->clkSrc) |
                          ohal_SetBits(SYSTICK_CSR_TICKINT, cfg->tickInt));

    if (err) {
        return err;
    }

    err = ohal_Reg_Update(reg, SYSTICK_RVR_REG, 
                          SYSTICK_RVR_RELOAD,
                          ohal_SetBits(SYSTICK_RVR_RELOAD, cfg->cyclesPerTick));

    return err;
}

static ohal_Error SysTick_Deinit(ohal_Timer *timerDev)
{
    return OHAL_SUCCESS;
}

static ohal_Error SysTick_Start(ohal_Timer *timerDev)
{
    ohal_Error err;
    ohal_Reg *reg = &timerDev->dev.reg;
    
    if (!timerDev || !timerDev->cfg) {
        return OHAL_EINVAL;
    }

    err = ohal_Reg_Update(reg, SYSTICK_CSR_REG, SYSTICK_CSR_ENABLE,
                          ohal_SetBits(SYSTICK_CSR_ENABLE, 1));

    return err;
}

static ohal_Error SysTick_Stop(ohal_Timer *timerDev)
{
    ohal_Error err;
    ohal_Reg *reg = &timerDev->dev.reg;
    
    if (!timerDev || !timerDev->cfg) {
        return OHAL_EINVAL;
    }

    err = ohal_Reg_Update(reg, SYSTICK_CSR_REG, SYSTICK_CSR_ENABLE,
                          ohal_SetBits(SYSTICK_CSR_ENABLE, 0));

    return err;
}

static ohal_Error SysTick_Reset(ohal_Timer *timerDev)
{

    return OHAL_SUCCESS;
}

ohal_TimerOps g_sysTickOps = {
    .Init = SysTick_Init,
    .Deinit = SysTick_Deinit,
    .Start = SysTick_Start,
    .Stop = SysTick_Stop,
    .Reset = SysTick_Reset,
};
