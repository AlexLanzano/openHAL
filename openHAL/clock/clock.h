#ifndef OHAL_CLOCK_H
#define OHAL_CLOCK_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

/**
 * @file clock.h
 * @brief Generic clock abstraction for configuring and controlling clock sources.
 */

typedef struct ohal_Clock ohal_Clock;

/**
 * @brief Driver vtable for clock devices.
 */
typedef struct {
    /** Initialize the clock hardware. */
    ohal_Error (*Init)(ohal_Clock *clkDev);
    /** Deinitialize the clock hardware. */
    ohal_Error (*Deinit)(ohal_Clock *clkDev);
    /** Enable the clock output. */
    ohal_Error (*Enable)(ohal_Clock *clkDev);
    /** Disable the clock output. */
    ohal_Error (*Disable)(ohal_Clock *clkDev);
    /** Read back the effective clock rate. */
    ohal_Error (*GetRate)(ohal_Clock *clkDev, size_t *rate);
    /** Issue driver-specific commands. */
    ohal_Error (*Cmd)(ohal_Clock *clkDev, size_t cmd, void *args);
} ohal_ClockDriver;

/**
 * @brief Clock device instance tying a register map, driver, and configuration.
 */
struct ohal_Clock {
    ohal_Device dev;
    ohal_ClockDriver *driver;
    void *cfg;
};

/**
 * @brief Initializes a clock device and its backing driver.
 *
 * @param clkDev Pointer to the clock instance to bring up.
 *
 * @retval OHAL_SUCCESS Driver-specific init routine ran successfully.
 * @retval OHAL_EINVAL  Null pointer or driver rejected the configuration.
 */
ohal_Error ohal_Clock_Init(ohal_Clock *clkDev);
/**
 * @brief Releases resources previously allocated for a clock device.
 *
 * @param clkDev Pointer to the clock instance to tear down.
 *
 * @retval OHAL_SUCCESS Driver-specific deinit routine ran successfully.
 * @retval OHAL_EINVAL  Null pointer or driver refused to deinitialize.
 */
ohal_Error ohal_Clock_Deinit(ohal_Clock *clkDev);
/**
 * @brief Enables the hardware clock so that downstream consumers can use it.
 *
 * @param clkDev Pointer to the clock instance to enable.
 *
 * @retval OHAL_SUCCESS Clock was enabled (or already running).
 * @retval OHAL_EINVAL  Null pointer or driver-specific enable failed.
 */
ohal_Error ohal_Clock_Enable(ohal_Clock *clkDev);
/**
 * @brief Disables the hardware clock to save power or enforce resets.
 *
 * @param clkDev Pointer to the clock instance to disable.
 *
 * @retval OHAL_SUCCESS Clock was disabled (or already stopped).
 * @retval OHAL_EINVAL  Null pointer or driver-specific disable failed.
 */
ohal_Error ohal_Clock_Disable(ohal_Clock *clkDev);
/**
 * @brief Reports the current output rate for a clock device.
 *
 * @param clkDev  Pointer to the clock instance being queried.
 * @param rate    Storage for the computed frequency in Hz.
 *
 * @retval OHAL_SUCCESS Result stored in @p rate.
 * @retval OHAL_EINVAL  Null pointer or driver could not provide a rate.
 */
ohal_Error ohal_Clock_GetRate(ohal_Clock *clkDev, size_t *rate);
/**
 * @brief Issues a driver-specific command to a clock device.
 *
 * @param clkDev Pointer to the clock instance receiving the command.
 * @param cmd    Numeric command selector defined by the driver.
 * @param args   Optional command arguments, interpreted per cmd.
 *
 * @retval OHAL_SUCCESS Command accepted and executed.
 * @retval OHAL_EINVAL  Null pointer, unknown command, or bad args.
 */
ohal_Error ohal_Clock_Cmd(ohal_Clock *clkDev, size_t cmd, void *args);

#endif /* OHAL_CLOCK_H */
