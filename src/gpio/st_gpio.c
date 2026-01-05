#include <openHAL/error.h>
#include <openHAL/gpio/gpio.h>
#include <openHAL/gpio/st_gpio.h>
#include <openHAL/reg.h>
#include <openHAL/bitops.h>

#define STGPIO_PORT_SIZE 0x400

#define STGPIO_GPIOx_MODE_REG     0x00
#define STGPIO_GPIOx_OUTTYPE_REG  0x04
#define STGPIO_GPIOx_SPEED_REG    0x08
#define STGPIO_GPIOx_PULL_REG     0x0C
#define STGPIO_GPIOx_IDR_REG      0x10
#define STGPIO_GPIOx_ODR_REG      0x14
#define STGPIO_GPIOx_ALTFNL_REG   0x20
#define STGPIO_GPIOx_ALTFNH_REG   0x24

static ohal_Error StGpio_GetPortAddr(ohal_Gpio *gpioDev, ohal_StGpio_Cfg *pinCfg, size_t *portAddr)
{
    ohal_StGpio_Port port = pinCfg->port;
    size_t regBase = gpioDev->dev.reg.base;

    if (port < OHAL_STGPIO_PORT_A || port > OHAL_STGPIO_PORT_H || !portAddr) {
        return OHAL_EINVAL;
    }

    *portAddr = (size_t)(regBase + (port * STGPIO_PORT_SIZE)); 

    return OHAL_SUCCESS;
}

static ohal_Error StGpio_InitMode(ohal_Reg *portReg, ohal_StGpio_Cfg *pinCfg)
{
    ohal_Error err;
    u8 pin = pinCfg->pin;
    u8 maskBit = pin << 1;
    size_t mask = OHAL_MASK_RANGE(maskBit + 1, maskBit);

    err = ohal_Reg_Set(portReg, STGPIO_GPIOx_MODE_REG,
                       ohal_SetBits(mask, pinCfg->mode));

    return err;
}

static ohal_Error StGpio_InitOutType(ohal_Reg *portReg, ohal_StGpio_Cfg *pinCfg)
{
    ohal_Error err;
    u8 pin = pinCfg->pin;
    size_t mask = OHAL_MASK(pin);

    err = ohal_Reg_Set(portReg, STGPIO_GPIOx_OUTTYPE_REG,
                       ohal_SetBits(mask, pinCfg->outType));

    return err;
}

static ohal_Error StGpio_InitSpeed(ohal_Reg *portReg, ohal_StGpio_Cfg *pinCfg)
{
    ohal_Error err;
    u8 pin = pinCfg->pin;
    u8 maskBit = pin << 1;
    size_t mask = OHAL_MASK_RANGE(maskBit + 1, maskBit);

    err = ohal_Reg_Set(portReg, STGPIO_GPIOx_SPEED_REG,
                       ohal_SetBits(mask, pinCfg->mode));

    return err;
}

static ohal_Error StGpio_InitAltFn(ohal_Reg *portReg, ohal_StGpio_Cfg *pinCfg)
{
    ohal_Error err;
    u8 pin = pinCfg->pin;
    size_t regOffset;
    u8 maskBit;
    size_t mask;

    if (pin >= 8) {
        regOffset = STGPIO_GPIOx_ALTFNH_REG;
        pin -= 8;
    } else {
        regOffset = STGPIO_GPIOx_ALTFNL_REG;
    }

    maskBit = pin << 2;
    mask = OHAL_MASK_RANGE(maskBit + 3, maskBit);

    err = ohal_Reg_Set(portReg, regOffset,
                       ohal_SetBits(mask, pinCfg->mode));

    return err;
}


static ohal_Error StGpio_InitPin(ohal_Gpio *gpioDev, ohal_StGpio_Cfg *pinCfg)
{
    ohal_Error err;
    ohal_Reg portReg;

    if (pinCfg->pin > 15) {
        return OHAL_EINVAL;
    }

    portReg.size = STGPIO_PORT_SIZE;
    err = StGpio_GetPortAddr(gpioDev, pinCfg, &portReg.base);
    if (err) {
        return err;
    }

    err = StGpio_InitMode(&portReg, pinCfg); 
    if (err) {
        return err;
    }

    err = StGpio_InitOutType(&portReg, pinCfg);
    if (err) {
        return err;
    }

    err = StGpio_InitSpeed(&portReg, pinCfg);
    if (err) {
        return err;
    }

    err = StGpio_InitAltFn(&portReg, pinCfg);
    if (err) {
        return err;
    }

    return OHAL_SUCCESS;
}

static ohal_Error StGpio_Init(ohal_Gpio *gpioDev)
{
    ohal_Error err;
    ohal_StGpio_Cfg *cfg;

    if (!gpioDev || !gpioDev->pinCfg || !gpioDev->pinCount) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StGpio_Cfg *)gpioDev->pinCfg;
    
    for (size_t pin = 0; pin < gpioDev->pinCount; ++pin) {
        err = StGpio_InitPin(gpioDev, &cfg[pin]);
        if (err) {
            return err;
        }

    }

    return OHAL_SUCCESS;
}

static ohal_Error StGpio_Deinit(ohal_Gpio *gpioDev)
{
    return OHAL_SUCCESS;
}

static ohal_Error StGpio_Get(ohal_Gpio *gpioDev, size_t pin, size_t *value)
{
    ohal_Error err;
    ohal_Reg portReg;
    ohal_StGpio_Cfg *cfg;
    size_t mask;

    if (!gpioDev || !gpioDev->pinCfg || !gpioDev->pinCount) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StGpio_Cfg *)gpioDev->pinCfg;


    if (cfg[pin].pin > 15) {
        return OHAL_EINVAL;
    }

    portReg.size = STGPIO_PORT_SIZE;
    err = StGpio_GetPortAddr(gpioDev, cfg, &portReg.base);
    if (err) {
        return err;
    }

    mask = OHAL_MASK(cfg[pin].pin);
    err = ohal_Reg_Get(&portReg, STGPIO_GPIOx_IDR_REG, mask, value);
    if (err) {
        return err;
    }

    return OHAL_SUCCESS;
}

static ohal_Error StGpio_Set(ohal_Gpio *gpioDev, size_t pin, size_t value)
{
    ohal_Error err;
    ohal_Reg portReg;
    ohal_StGpio_Cfg *cfg;
    size_t mask;

    if (!gpioDev || !gpioDev->pinCfg || !gpioDev->pinCount) {
        return OHAL_EINVAL;
    }

    cfg = (ohal_StGpio_Cfg *)gpioDev->pinCfg;


    if (cfg[pin].pin > 15) {
        return OHAL_EINVAL;
    }

    portReg.size = STGPIO_PORT_SIZE;
    err = StGpio_GetPortAddr(gpioDev, cfg, &portReg.base);
    if (err) {
        return err;
    }

    mask = OHAL_MASK(cfg[pin].pin);
    err = ohal_Reg_Set(&portReg, STGPIO_GPIOx_ODR_REG,
                       ohal_SetBits(mask, value));
    if (err) {
        return err;
    }

    return OHAL_SUCCESS;
}

static ohal_Error StGpio_Cmd(ohal_Gpio *gpioDev, size_t cmd, void *args)
{
    return OHAL_SUCCESS;
}

ohal_GpioOps g_stGpioOps = {
    .Init = StGpio_Init,
    .Deinit = StGpio_Deinit,
    .Get = StGpio_Get,
    .Set = StGpio_Set,
    .Cmd = StGpio_Cmd,
};
