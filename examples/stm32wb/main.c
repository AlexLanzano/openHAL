#include <openHAL/openHAL.h>
#include <openHAL/clock/st_clock.h>

extern ohal_ClockOps g_stClockOps;

ohal_StClock_Cfg clkCfg = {
    
};

ohal_Clock clk = {
    .dev = {
        .name = "pllClk",
        .reg = {
            .addr = 0x10000000,
            .size = 0x400,
        },
    },
    .ops = &g_stClockOps,
    .cfg = &clkCfg,
};

void main(void)
{
    ohal_Error err;
    size_t rate;

    err = ohal_Clock_Init(&clk); 
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Init");
        goto loop;
    }

    err = ohal_Clock_Enable(&clk);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Enable");
        goto loop;
    }

    err = ohal_Clock_GetRate(&clk, &rate);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_GetRate");
        goto loop;
    }

    ohal_PrintInfo("Clock rate is %lu\n", rate);

    err = ohal_Clock_Disable(&clk);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Disable");
        goto loop;
    }

    err = ohal_Clock_Deinit(&clk);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Deinit");
        goto loop;
    }

loop:
    while (1);

}
