#ifndef OHAL_DEVICE_H
#define OHAL_DEVICE_H

#include <openHAL/reg.h>

/**
 * @file device.h
 * @brief Base descriptor shared by all openHAL devices.
 */

#define OHAL_MAX_DEV_NAME_LEN 256

/**
 * @brief Generic device descriptor containing an identifying name and register map.
 */
typedef struct ohal_Device {
    char name[OHAL_MAX_DEV_NAME_LEN];
    ohal_Reg reg;
} ohal_Device;

#endif /* OHAL_DEVICE_H */
