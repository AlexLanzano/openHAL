#ifndef OHAL_BITOPS_H
#define OHAL_BITOPS_H

#if defined(__GNUC__)
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

#define ohal_SetBits(mask, value) \
    (((value) << ohal_CountTrailingZeros(mask)) & (mask))

#define ohal_GetBits(mask, reg) \
    (((reg) & (mask)) >> ohal_CountTrailingZeros(mask))

#define OHAL_MASK(bit) \
    (1ul << bit)

#define OHAL_MASK_RANGE(high_bit, low_bit) \
    ((((1ul << (((high_bit) - (low_bit)) + 1)) - 1ul)) << (low_bit))

#endif /* OHAL_BITOPS_H */
