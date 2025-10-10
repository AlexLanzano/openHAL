#ifndef OHAL_ERROR_H
#define OHAL_ERROR_H

#include <openHAL/types.h>

typedef s16 ohal_Error;

enum {
    OHAL_SUCCESS = 0,
    OHAL_EINVAL = -4000,
};

#endif /* OHAL_ERROR_H */
