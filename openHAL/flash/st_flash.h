#ifndef OHAL_ST_FLASH_H
#define OHAL_ST_FLASH_H

#include <openHAL/types.h>
#include <openHAL/flash/flash.h>

/**
 * @file st_flash.h
 * @brief STM32-specific flash driver configuration and commands.
 */

/**
 * @brief STM32 flash configuration placeholder. Extend as options are needed.
 */
typedef struct ohal_StFlash_Cfg {
} ohal_StFlash_Cfg;

/**
 * @brief Latency wait-state settings for STM32 flash.
 */
enum ohal_StFlash_Latency {
    OHAL_ST_FLASH_LATENCY_0,
    OHAL_ST_FLASH_LATENCY_1,
    OHAL_ST_FLASH_LATENCY_2,
    OHAL_ST_FLASH_LATENCY_3,
};

/**
 * @brief Command arguments for changing flash latency.
 */
typedef struct ohal_StFlash_SetLatencyArgs {
    enum ohal_StFlash_Latency latency;
} ohal_StFlash_SetLatencyArgs;

/**
 * @brief STM32 flash driver command selectors.
 */
enum ohal_StFlash_Cmd {
    OHAL_ST_FLASH_CMD_SET_LATENCY,
};

/** Driver instance for STM32 flash. */
extern ohal_FlashDriver g_stFlashDriver;

#endif /* OHAL_ST_FLASH_H */
