#include <openHAL/timer/timer.h>
#include <openHAL/error.h>
#include <openHAL/print.h>
#include <openHAL/reg.h>
#include <openHAL/bitops.h>

inline ohal_Error ohal_Timer_Init(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->ops || !timerDev->ops->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->ops->Init(timerDev);
}

inline ohal_Error ohal_Timer_Deinit(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->ops || !timerDev->ops->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->ops->Deinit(timerDev);
}

inline ohal_Error ohal_Timer_Start(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->ops || !timerDev->ops->Start) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->ops->Start(timerDev);
}

inline ohal_Error ohal_Timer_Stop(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->ops || !timerDev->ops->Stop) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->ops->Stop(timerDev);
}

inline ohal_Error ohal_Timer_Reset(ohal_Timer *timerDev)
{
    if (!timerDev || !timerDev->ops || !timerDev->ops->Reset) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return timerDev->ops->Reset(timerDev);
}
