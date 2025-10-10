#ifndef OHAL_CLOCK_H
#define OHAL_CLOCK_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

typedef struct ohal_Clock ohal_Clock;

typedef struct {
    ohal_Error (*Init)(ohal_Clock *clkDev);
    ohal_Error (*Deinit)(ohal_Clock *clkDev);
    ohal_Error (*Enable)(ohal_Clock *clkDev);
    ohal_Error (*Disable)(ohal_Clock *clkDev);
    ohal_Error (*GetRate)(ohal_Clock *clkDev, size_t *rateOut);
    ohal_Error (*Cmd)(ohal_Clock *clkDev, size_t cmd, void *args);
} ohal_ClockOps;

struct ohal_Clock {
    ohal_Device dev;
    ohal_ClockOps *ops;
    void *cfg;
};

ohal_Error ohal_Clock_Init(ohal_Clock *clkDev);
ohal_Error ohal_Clock_Deinit(ohal_Clock *clkDev);
ohal_Error ohal_Clock_Enable(ohal_Clock *clkDev);
ohal_Error ohal_Clock_Disable(ohal_Clock *clkDev);
ohal_Error ohal_Clock_GetRate(ohal_Clock *clkDev, size_t *rateOut);
ohal_Error ohal_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args);

#endif /* OHAL_CLOCK_H */
