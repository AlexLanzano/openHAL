#ifndef OHAL_GPIO_H
#define OHAL_GPIO_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

typedef struct ohal_Gpio ohal_Gpio;

typedef struct {
    ohal_Error (*Init)(ohal_Gpio *gpioDev); 
    ohal_Error (*Deinit)(ohal_Gpio *gpioDev); 
    ohal_Error (*Get)(ohal_Gpio *gpioDev, size_t pin, size_t *value); 
    ohal_Error (*Set)(ohal_Gpio *gpioDev, size_t pin, size_t value); 
    ohal_Error (*Cmd)(ohal_Gpio *gpioDev, size_t cmd, void *args);
} ohal_GpioOps;

struct ohal_Gpio {
    ohal_Device dev;
    ohal_GpioOps *ops;
    void *pinCfg;
    size_t pinCount;
};

ohal_Error ohal_Gpio_Init(ohal_Gpio *gpioDev);
ohal_Error ohal_Gpio_Deinit(ohal_Gpio *gpioDev);
ohal_Error ohal_Gpio_Get(ohal_Gpio *gpioDev, size_t pin, size_t *value);
ohal_Error ohal_Gpio_Set(ohal_Gpio *gpioDev, size_t pin, size_t value);
ohal_Error ohal_Gpio_Cmd(ohal_Gpio *gpioDev, size_t cmd, void *args);

#endif /* OHAL_GPIO_H */
