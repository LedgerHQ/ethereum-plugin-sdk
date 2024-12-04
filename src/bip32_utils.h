#pragma once

#include <stdint.h>
#include "bip32.h"

typedef struct bip32_path_t {
    uint8_t length;
    uint32_t path[MAX_BIP32_PATH];
} bip32_path_t;
