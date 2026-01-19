#ifndef OHAL_BITOPS_H
#define OHAL_BITOPS_H

/**
 * @file bitops.h
 * @brief Bit manipulation helpers for register fields.
 */

#if defined(__GNUC__)
/** Count trailing zeros in a mask. */
#define ohal_CountTrailingZeros(mask) __builtin_ctz(mask)
#else
static size_t ohal_CountTrailingZeros(mask)
{
    size_t cnt = 0;
    while ((mask & 1ul) == 0ul) {
        mask >>= 1;
        n++;
    }

    return n;
}
#endif

/**
 * @brief Encode a value into a bit field described by @p mask.
 */
#define ohal_SetBits(mask, value) \
    (((value) << ohal_CountTrailingZeros(mask)) & (mask))

/**
 * @brief Extract a bit field value from a register using @p mask.
 */
#define ohal_GetBits(mask, reg) \
    (((reg) & (mask)) >> ohal_CountTrailingZeros(mask))

/** Create a single-bit mask for bit @p bit. */
#define OHAL_MASK(bit) \
    (1ul << bit)

/** Create a mask covering bits @p high_bit down to @p low_bit (inclusive). */
#define OHAL_MASK_RANGE(high_bit, low_bit) \
    ((((1ul << (((high_bit) - (low_bit)) + 1)) - 1ul)) << (low_bit))

#endif /* OHAL_BITOPS_H */
