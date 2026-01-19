#ifndef OHAL_TIMER_H
#define OHAL_TIMER_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

/**
 * @file timer.h
 * @brief Generic timer abstraction for periodic events or counters.
 */

typedef struct ohal_Timer ohal_Timer;

/**
 * @brief Driver vtable for timer devices.
 */
typedef struct {
    /** Initialize the timer hardware. */
    ohal_Error (*Init)(ohal_Timer *timerDev);
    /** Deinitialize the timer hardware. */
    ohal_Error (*Deinit)(ohal_Timer *timerDev);
    /** Start the timer running. */
    ohal_Error (*Start)(ohal_Timer *timerDev);
    /** Stop the timer. */
    ohal_Error (*Stop)(ohal_Timer *timerDev);
    /** Reset the timer counter and configuration as needed. */
    ohal_Error (*Reset)(ohal_Timer *timerDev);
} ohal_TimerDriver;

/**
 * @brief Timer device instance pairing configuration with a driver.
 */
struct ohal_Timer{
    ohal_Device dev;
    ohal_TimerDriver *driver;
    void *cfg;
};

/**
 * @brief Initialize a timer device.
 *
 * @param timerDev Timer instance to initialize.
 *
 * @retval OHAL_SUCCESS Driver-specific init completed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Timer_Init(ohal_Timer *timerDev);
/**
 * @brief Deinitialize a timer device.
 *
 * @param timerDev Timer instance to deinitialize.
 *
 * @retval OHAL_SUCCESS Driver-specific deinit completed.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Timer_Deinit(ohal_Timer *timerDev);
/**
 * @brief Start a timer.
 *
 * @param timerDev Timer instance to start.
 *
 * @retval OHAL_SUCCESS Timer started.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Timer_Start(ohal_Timer *timerDev);
/**
 * @brief Stop a timer.
 *
 * @param timerDev Timer instance to stop.
 *
 * @retval OHAL_SUCCESS Timer stopped.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Timer_Stop(ohal_Timer *timerDev);
/**
 * @brief Reset a timer.
 *
 * @param timerDev Timer instance to reset.
 *
 * @retval OHAL_SUCCESS Timer reset.
 * @retval OHAL_EINVAL  Null pointer or missing callbacks.
 */
ohal_Error ohal_Timer_Reset(ohal_Timer *timerDev);

#endif /* OHAL_TIMER_H */
