#include <openHAL/error.h>
#include <openHAL/clock/clock.h>
#include <openHAL/clock/st_clock.h>
#include <openHAL/reg.h>
#include <openHAL/bitops.h>

#define STCLOCK_CR_REG 0x000
#define STCLOCK_CR_PLLON_MASK OHAL_MASK(24)

#define STCLOCK_CFGR_REG 0x008
#define STCLOCK_CFGR_SW OHAL_MASK_RANGE(1, 0)
#define STCLOCK_CFGR_SWS OHAL_MASK_RANGE(3, 2)
#define STCLOCK_CFGR_HPRE OHAL_MASK_RANGE(7, 4)
#define STCLOCK_CFGR_PPRE1 OHAL_MASK_RANGE(10, 8)
#define STCLOCK_CFGR_PPRE2 OHAL_MASK_RANGE(13, 11)
#define STCLOCK_CFGR_STOPWUCK OHAL_MASK(15)
#define STCLOCK_CFGR_HPREF OHAL_MASK(16)
#define STCLOCK_CFGR_PPRE1F OHAL_MASK(17)
#define STCLOCK_CFGR_PPRE2F OHAL_MASK(18)
#define STCLOCK_CFGR_MCOSEL OHAL_MASK_RANGE(27, 24)
#define STCLOCK_CFGR_MCOPRE OHAL_MASK_RANGE(30, 28)

#define STCLOCK_PLLCFGR_REG 0x00C
#define STCLOCK_PLLCFGR_PLLSRC_MASK OHAL_MASK_RANGE(1, 0)
#define STCLOCK_PLLCFGR_PLLM_MASK   OHAL_MASK_RANGE(6, 4)
#define STCLOCK_PLLCFGR_PLLN_MASK   OHAL_MASK_RANGE(14, 8)
#define STCLOCK_PLLCFGR_PLLP_MASK   OHAL_MASK_RANGE(21, 17)
#define STCLOCK_PLLCFGR_PLLQ_MASK   OHAL_MASK_RANGE(27, 25)
#define STCLOCK_PLLCFGR_PLLR_MASK   OHAL_MASK_RANGE(31, 29)

#define STCLOCK_AHB2ENR_REG 0x04C
#define STCLOCK_AHB2ENR_GPIOAEN OHAL_MASK(0)
#define STCLOCK_AHB2ENR_GPIOBEN OHAL_MASK(1)
#define STCLOCK_AHB2ENR_GPIOCEN OHAL_MASK(2)
#define STCLOCK_AHB2ENR_GPIODEN OHAL_MASK(3)
#define STCLOCK_AHB2ENR_GPIOEEN OHAL_MASK(4)
#define STCLOCK_AHB2ENR_GPIOHEN OHAL_MASK(7)
#define STCLOCK_AHB2ENR_ADCEN   OHAL_MASK(13)
#define STCLOCK_AHB2ENR_AES1EN  OHAL_MASK(16)

#define STCLOCK_APB1ENR_REG 0x05C
#define STCLOCK_APB1ENR_LPUART1EN OHAL_MASK(0)
#define STCLOCK_APB1ENR_LPTIM2EN    OHAL_MASK(5)

static ohal_Error StClock_InitPllClk(ohal_Clock *clkDev,
                                     ohal_StClock_Cfg *cfg,
                                     ohal_StClock_PllClkCfg *pllCfg)
{
    ohal_Error err;
    ohal_Reg *reg = &clkDev->dev.reg;

    err = ohal_Reg_Set(reg, STCLOCK_PLLCFGR_REG,
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLSRC_MASK, pllCfg->clkSrc) |
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLM_MASK, pllCfg->m) |
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLN_MASK, pllCfg->n) |
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLP_MASK, pllCfg->p) |
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLQ_MASK, pllCfg->q) |
                       ohal_SetBits(STCLOCK_PLLCFGR_PLLR_MASK, pllCfg->r));
    if (err) {
        return err;
    }

    return OHAL_SUCCESS;
}

static ohal_Error StClock_Init(ohal_Clock *clkDev)
{
    ohal_Error err;
    ohal_StClock_Cfg *cfg;

    if (!clkDev || !clkDev->cfg) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StClock_Cfg *)clkDev->cfg;

    switch (cfg->sysClkSrc) {
    case OHAL_ST_CLOCK_SRC_PLL: {
        err = StClock_InitPllClk(clkDev, cfg, &cfg->sysClkCfg.pll);

    } break;
    default:
        err = OHAL_EINVAL;
    }

    return err;
}

static ohal_Error StClock_Deinit(ohal_Clock *clkDev)
{
    return OHAL_SUCCESS;
}

static ohal_Error StClock_Enable(ohal_Clock *clkDev)
{
    ohal_Error err;
    ohal_StClock_Cfg *cfg;

    if (!clkDev || !clkDev->cfg) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StClock_Cfg *)clkDev->cfg;

    if (cfg->sysClkSrc == OHAL_ST_CLOCK_SRC_PLL) {
        err = ohal_Reg_Update(&clkDev->dev.reg, STCLOCK_CR_REG, STCLOCK_CR_PLLON_MASK,
                              ohal_SetBits(STCLOCK_CR_PLLON_MASK, 1));
        if (err) {
            return err;
        }
    }

    for (int i = 0; i < cfg->periphClkEnCount; ++i) {
        if (cfg->periphClkEn[i] == OHAL_ST_CLOCK_PERIPH_GPIOA) {
            err = ohal_Reg_Update(&clkDev->dev.reg, STCLOCK_AHB2ENR_REG, STCLOCK_AHB2ENR_GPIOAEN,
                               ohal_SetBits(STCLOCK_AHB2ENR_GPIOAEN, 1));
            if (err) {
                return err;
            }
        }
        if (cfg->periphClkEn[i] == OHAL_ST_CLOCK_PERIPH_GPIOB) {
            err = ohal_Reg_Update(&clkDev->dev.reg, STCLOCK_AHB2ENR_REG, STCLOCK_AHB2ENR_GPIOBEN,
                               ohal_SetBits(STCLOCK_AHB2ENR_GPIOBEN, 1));
            if (err) {
                return err;
            }
        }
    }


    return OHAL_SUCCESS;
}

static ohal_Error StClock_Disable(ohal_Clock *clkDev)
{
    ohal_Error err;
    ohal_StClock_Cfg *cfg;

    if (!clkDev || !clkDev->cfg) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StClock_Cfg *)clkDev->cfg;

    if (cfg->sysClkSrc == OHAL_ST_CLOCK_SRC_PLL) {
        err = ohal_Reg_Set(&clkDev->dev.reg, STCLOCK_CR_REG,
                           ohal_SetBits(STCLOCK_CR_PLLON_MASK, 0));
        if (err) {
            return err;
        }
    }

    for (int i = 0; i < cfg->periphClkEnCount; ++i) {
        if (cfg->periphClkEn[i] == OHAL_ST_CLOCK_PERIPH_GPIOA) {
            err = ohal_Reg_Set(&clkDev->dev.reg, STCLOCK_AHB2ENR_REG,
                               ohal_SetBits(STCLOCK_AHB2ENR_GPIOAEN, 0));
            if (err) {
                return err;
            }
        }
    }

    return OHAL_SUCCESS;
}

static ohal_Error StClock_GetRate(ohal_Clock *clkDev, size_t *rateOut)
{
    return OHAL_SUCCESS;
}

static ohal_Error StClock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args)
{
    return OHAL_SUCCESS;
}

ohal_ClockOps g_stClockOps = {
    .Init = StClock_Init,
    .Deinit = StClock_Deinit,
    .Enable = StClock_Enable,
    .Disable = StClock_Disable,
    .GetRate = StClock_GetRate,
    .Cmd = StClock_Cmd,
};
