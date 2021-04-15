/* This file is auto-generated, don't edit it */

#pragma once

#include "os.h"
#include "cx.h"

#define MAX_TICKER_LEN 12  // 10 characters + ' ' + '\0'

typedef struct tokenDefinition_t {
#ifdef HAVE_CONTRACT_NAME_IN_DESCRIPTOR
    uint8_t contractName[20];
#endif
    uint8_t address[20];
    uint8_t ticker[MAX_TICKER_LEN];
    uint8_t decimals;
} tokenDefinition_t;

typedef struct txInt256_t {
    uint8_t value[32];
    uint8_t length;
} txInt256_t;

typedef struct txContent_t {
    txInt256_t gasprice;
    txInt256_t startgas;
    txInt256_t value;
    txInt256_t nonce;
    uint8_t destination[20];
    uint8_t destinationLength;
    uint8_t v[4];
    uint8_t vLength;
} txContent_t;
