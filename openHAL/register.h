#ifndef OHAL_REGISTER_H
#define OHAL_REGISTER_H

#include <stddef.h>

typedef struct ohal_Register {
    size_t addr;
    size_t size;
} ohal_Register;

#endif /* OHAL_REGISTER_H */

