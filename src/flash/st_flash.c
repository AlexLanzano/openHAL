#include <openHAL/flash/st_flash.h>
#include <openHAL/flash/flash.h>
#include <openHAL/error.h>
#include <openHAL/bitops.h>

#define ST_FLASH_ACR_REG 0x00
#define ST_FLASH_ACR_LATENCY OHAL_MASK_RANGE(2, 0)

static ohal_Error StFlash_Init(ohal_Flash *flashDev)
{
    (void)flashDev;
    return OHAL_SUCCESS;
}

static ohal_Error StFlash_Deinit(ohal_Flash *flashDev)
{
    (void)flashDev;
    return OHAL_SUCCESS;
}

static ohal_Error StFlash_Write(ohal_Flash *flashDev, size_t addr, u8 *data,
                                size_t dataSz)
{
    (void)flashDev;
    (void)addr;
    (void)data;
    (void)dataSz;
    return OHAL_SUCCESS;
}

static ohal_Error StFlash_Erase(ohal_Flash *flashDev, size_t addr,
                                size_t dataSz)
{
    (void)flashDev;
    (void)addr;
    (void)dataSz;
    return OHAL_SUCCESS;
}

static ohal_Error StFlash_Cmd_SetLatency(ohal_Flash *flashDev, ohal_StFlash_SetLatencyArgs *args)
{
    if (!args) {
        return OHAL_EINVAL;
    }

    ohal_Reg *reg = &flashDev->dev.reg;
    return ohal_Reg_Update(reg, ST_FLASH_ACR_REG, ST_FLASH_ACR_LATENCY, args->latency);
}

static ohal_Error StFlash_Cmd(ohal_Flash *flashDev, size_t cmd, void *args)
{
    switch (cmd) {
    case OHAL_ST_FLASH_CMD_SET_LATENCY:
        return StFlash_Cmd_SetLatency(flashDev, args);

    default:
        return OHAL_EINVAL;
    }
    
    return OHAL_SUCCESS;
}

ohal_FlashDriver g_stFlashDriver = {
    .Init = StFlash_Init,
    .Deinit = StFlash_Deinit,
    .Write = StFlash_Write,
    .Erase = StFlash_Erase,
    .Cmd = StFlash_Cmd,
};
