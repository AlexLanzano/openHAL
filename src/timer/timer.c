#include <openHAL/timer/timer.h>
#include <openHAL/error.h>
#include <openHAL/print.h>
#include <openHAL/reg.h>
#include <openHAL/bitops.h>

inline ohal_Error ohal_Timer_Init(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->driver || !timerDev->driver->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->driver->Init(timerDev);
}

inline ohal_Error ohal_Timer_Deinit(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->driver || !timerDev->driver->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->driver->Deinit(timerDev);
}

inline ohal_Error ohal_Timer_Start(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->driver || !timerDev->driver->Start) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->driver->Start(timerDev);
}

inline ohal_Error ohal_Timer_Stop(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->driver || !timerDev->driver->Stop) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->driver->Stop(timerDev);
}

inline ohal_Error ohal_Timer_Reset(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->driver || !timerDev->driver->Reset) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->driver->Reset(timerDev);
}
