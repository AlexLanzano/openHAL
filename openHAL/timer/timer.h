#ifndef OHAL_TIMER_H
#define OHAL_TIMER_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

typedef struct ohal_Timer ohal_Timer;

typedef struct {
    ohal_Error (*Init)(ohal_Timer *timerDev);
    ohal_Error (*Deinit)(ohal_Timer *timerDev);
    ohal_Error (*Start)(ohal_Timer *timerDev);
    ohal_Error (*Stop)(ohal_Timer *timerDev);
    ohal_Error (*Reset)(ohal_Timer *timerDev);
} ohal_TimerOps;

struct ohal_Timer{
    ohal_Device dev;
    ohal_TimerOps *ops;
    void *cfg;
};

ohal_Error ohal_Timer_Init(ohal_Timer *timerDev);
ohal_Error ohal_Timer_Deinit(ohal_Timer *timerDev);
ohal_Error ohal_Timer_Start(ohal_Timer *timerDev);
ohal_Error ohal_Timer_Stop(ohal_Timer *timerDev);
ohal_Error ohal_Timer_Reset(ohal_Timer *timerDev);

#endif /* OHAL_TIMER_H */
