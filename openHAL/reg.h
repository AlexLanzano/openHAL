#ifndef OHAL_REGMAP_H
#define OHAL_REGMAP_H

#include <stddef.h>
#include <openHAL/error.h>

typedef struct ohal_Reg {
    size_t base;
    size_t size;
} ohal_Reg;

ohal_Error ohal_Reg_Update(ohal_Reg *regmap, size_t offset, size_t mask, size_t value);
ohal_Error ohal_Reg_Get(ohal_Reg *regmap, size_t offset, size_t mask, size_t *value);

#endif /* OHAL_REGMAP_H */
