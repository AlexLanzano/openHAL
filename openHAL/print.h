#ifndef OHAL_PRINT_H
#define OHAL_PRINT_H

/**
 * @file print.h
 * @brief Logging macros used by openHAL. These are weak by default and can be
 *        overridden by platform code to route logs appropriately.
 */

/** Log an error with an associated error code. */
#define ohal_PrintErr(err, format, ...)
/** Log a warning message. */
#define ohal_PrintWarn(format, ...)
/** Log an informational message. */
#define ohal_PrintInfo(format, ...)
/** Log a verbose debug message. */
#define ohal_PrintDebug(format, ...)

#endif /* OHAL_PRINT_H */
