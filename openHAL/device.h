#ifndef OHAL_DEVICE_H
#define OHAL_DEVICE_H

#include <openHAL/reg.h>

#define OHAL_MAX_DEV_NAME_LEN 256

typedef struct ohal_Device {
    char name[OHAL_MAX_DEV_NAME_LEN];
    ohal_Reg reg;
} ohal_Device;

#endif /* OHAL_DEVICE_H */

