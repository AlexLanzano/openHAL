#ifndef OHAL_ERROR_H
#define OHAL_ERROR_H

#include <openHAL/types.h>

/**
 * @file error.h
 * @brief Shared error codes for openHAL APIs.
 */

/** Signed 16-bit status code type used by openHAL. */
typedef s16 ohal_Error;

enum {
    /** Operation completed successfully. */
    OHAL_SUCCESS = 0,
    /** Invalid argument or unsupported operation. */
    OHAL_EINVAL = -4000,
};

#endif /* OHAL_ERROR_H */
