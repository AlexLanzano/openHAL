#ifndef OHAL_STGPIO_H
#define OHAL_STGPIO_H

#include <openHAL/types.h>

typedef enum {
    OHAL_STGPIO_PORT_A,
    OHAL_STGPIO_PORT_B,
    OHAL_STGPIO_PORT_C,
    OHAL_STGPIO_PORT_D,
    OHAL_STGPIO_PORT_E,
    OHAL_STGPIO_PORT_F,
    OHAL_STGPIO_PORT_G,
    OHAL_STGPIO_PORT_H,
} ohal_StGpio_Port;

typedef enum {
    OHAL_STGPIO_MODE_IN,
    OHAL_STGPIO_MODE_OUT,
    OHAL_STGPIO_MODE_ALTFN,
    OHAL_STGPIO_MODE_ANALOG,
} ohal_StGpio_Mode;

typedef enum {
    OHAL_STGPIO_OUTTYPE_PUSHPULL,
    OHAL_STGPIO_OUTTYPE_OPENDRAIN,
} ohal_StGpio_OutType;

typedef enum {
    OHAL_STGPIO_SPEED_LOW,
    OHAL_STGPIO_SPEED_MEDIUM,
    OHAL_STGPIO_SPEED_FAST,
    OHAL_STGPIO_SPEED_HIGH,
} ohal_StGpio_Speed;

typedef enum {
    OHAL_STGPIO_PULL_NONE,
    OHAL_STGPIO_PULL_UP,
    OHAL_STGPIO_PULL_DOWN,
} ohal_StGpio_Pull;

typedef struct {
    ohal_StGpio_Port port;
    u8 pin;
    ohal_StGpio_Mode mode;
    ohal_StGpio_OutType outType;
    ohal_StGpio_Speed speed;
    ohal_StGpio_Pull pull;
    u8 altFn;
} ohal_StGpio_Cfg;
#endif /* OHAL_STGPIO_H */
