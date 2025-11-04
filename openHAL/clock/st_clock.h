#ifndef OHAL_ST_CLOCK_H
#define OHAL_ST_CLOCK_H

#include <openHAL/types.h>

typedef enum {
    OHAL_ST_CLOCK_SRC_NONE,
    OHAL_ST_CLOCK_SRC_HSI16,
    OHAL_ST_CLOCK_SRC_MSI,
    OHAL_ST_CLOCK_SRC_HSE,
    OHAL_ST_CLOCK_SRC_PLL,
    OHAL_ST_CLOCK_SRC_LSE,
    OHAL_ST_CLOCK_SRC_LSI,

} ohal_StClock_ClockSrc;

typedef struct ohal_StClock_Cfg {
    ohal_StClock_ClockSrc sysClk;
    
} ohal_StClock_Cfg;


#endif /* OHAL_ST_CLOCK_H */
