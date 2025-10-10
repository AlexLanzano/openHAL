#ifndef EX_DEV_CFG_H
#define EX_DEV_CFG_H

ohal_ClockOps clkOps = {OHAL_ST_HAL_CLOCK_OPS};

ohal_StHalClockCfg clkCfg = {
    
};

ohal_Clock clk = {
    .dev = {
        .name = "pllClk",
        .reg = {
            .addr = 0x10000000,
            .size = 0x400,
        },
    },
    .ops = &clkOps,
    .cfg = &clkCfg,
};

#endif /* EX_DEV_CFG_H */
