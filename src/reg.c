#include <openHAL/reg.h>
#include <openHAL/error.h>
#include <openHAL/bitops.h>
#include <stddef.h>

ohal_Error ohal_Reg_Update(ohal_Reg *regmap, size_t offset, size_t mask, size_t value)
{
    volatile size_t *reg;
    if (!regmap || offset > regmap->size) {
        return OHAL_EINVAL;
    }

    reg = (size_t *)(regmap->base + offset);
    *reg = (*reg & ~mask) | (value & mask);

    return OHAL_SUCCESS;
}

ohal_Error ohal_Reg_Get(ohal_Reg *regmap, size_t offset, size_t mask, size_t *value)
{
    size_t val;
    if (!regmap || offset > regmap->size || !value) {
        return OHAL_EINVAL;
    }

    val = *(volatile size_t *)(regmap->base + offset);
    *value = ohal_GetBits(mask, val);

    return OHAL_SUCCESS;
}
