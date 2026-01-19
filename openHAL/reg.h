#ifndef OHAL_REGMAP_H
#define OHAL_REGMAP_H

#include <stddef.h>
#include <openHAL/error.h>

/**
 * @file reg.h
 * @brief Helpers for accessing and manipulating memory-mapped registers.
 */

/**
 * @brief Description of a contiguous register map.
 */
typedef struct ohal_Reg {
    size_t base;
    size_t size;
} ohal_Reg;

/**
 * @brief Update a masked field within a memory-mapped register.
 *
 * The function applies a read-modify-write using @p mask to only touch the
 * desired bit field.
 *
 * @param regmap Target register map descriptor.
 * @param offset Byte offset from @p regmap->base to the register.
 * @param mask   Bit mask selecting the field to update.
 * @param value  Value to write, which will be masked and shifted.
 *
 * @retval OHAL_SUCCESS Update completed.
 * @retval OHAL_EINVAL  Null pointer or offset beyond region size.
 */
ohal_Error ohal_Reg_Update(ohal_Reg *regmap, size_t offset, size_t mask, size_t value);
/**
 * @brief Read a masked field from a memory-mapped register.
 *
 * @param regmap Target register map descriptor.
 * @param offset Byte offset from @p regmap->base to the register.
 * @param mask   Bit mask selecting the field to extract.
 * @param value  Output storage for the decoded field.
 *
 * @retval OHAL_SUCCESS Value read and stored.
 * @retval OHAL_EINVAL  Null pointer, offset beyond region size, or bad output pointer.
 */
ohal_Error ohal_Reg_Get(ohal_Reg *regmap, size_t offset, size_t mask, size_t *value);

#endif /* OHAL_REGMAP_H */
