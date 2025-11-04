#ifndef OHAL_DEVICE_H
#define OHAL_DEVICE_H

#include <openHAL/register.h>

#define OHAL_MAX_DEV_NAME_LEN 256

typedef struct ohal_Device {
    char name[OHAL_MAX_DEV_NAME_LEN];
    ohal_Register reg;
} ohal_Device;

#endif /* OHAL_DEVICE_H */

