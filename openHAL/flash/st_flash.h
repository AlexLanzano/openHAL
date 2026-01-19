#ifndef OHAL_ST_FLASH_H
#define OHAL_ST_FLASH_H

#include <openHAL/types.h>
#include <openHAL/flash/flash.h>

typedef struct ohal_StFlash_Cfg {
} ohal_StFlash_Cfg;

enum ohal_StFlash_Latency {
    OHAL_ST_FLASH_LATENCY_0,
    OHAL_ST_FLASH_LATENCY_1,
    OHAL_ST_FLASH_LATENCY_2,
    OHAL_ST_FLASH_LATENCY_3,
};

typedef struct ohal_StFlash_SetLatencyArgs {
    enum ohal_StFlash_Latency latency;
} ohal_StFlash_SetLatencyArgs;

enum ohal_StFlash_Cmd {
    OHAL_ST_FLASH_CMD_SET_LATENCY,
};

extern ohal_FlashDriver g_stFlashDriver;

#endif /* OHAL_ST_FLASH_H */
