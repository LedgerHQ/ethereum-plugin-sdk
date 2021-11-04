/* This file is auto-generated, don't edit it */

#pragma once

#include "os.h"
#include "cx.h"
#include <stdbool.h>
#include <string.h>

#define MAX_TICKER_LEN 12  // 10 characters + ' ' + '\0'

#define ADDRESS_LENGTH 20

#define INT256_LENGTH 32

#define WEI_TO_ETHER 18

#define SELECTOR_SIZE 4

#define PARAMETER_LENGTH 32

#define RUN_APPLICATION 1

typedef struct tokenDefinition_t {
#ifdef HAVE_CONTRACT_NAME_IN_DESCRIPTOR
    uint8_t contractName[ADDRESS_LENGTH];
#endif
    uint8_t address[ADDRESS_LENGTH];
    char ticker[MAX_TICKER_LEN];
    uint8_t decimals;
} tokenDefinition_t;

typedef struct txInt256_t {
    uint8_t value[INT256_LENGTH];
    uint8_t length;
} txInt256_t;

typedef struct txContent_t {
    txInt256_t gasprice;  // Used as MaxFeePerGas when dealing with EIP1559 transactions.
    txInt256_t startgas;  // Also known as `gasLimit`.
    txInt256_t value;
    txInt256_t nonce;
    txInt256_t chainID;
    uint8_t destination[ADDRESS_LENGTH];
    uint8_t destinationLength;
    uint8_t v[8];
    uint8_t vLength;
    bool dataPresent;
} txContent_t;

static __attribute__((no_instrument_function)) inline int allzeroes(void *buf, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    for (size_t i = 0; i < n; ++i) {
        if (p[i]) {
            return 0;
        }
    }
    return 1;
}

static const char HEXDIGITS[] = "0123456789abcdef";

void getEthAddressStringFromBinary(uint8_t *address,
                                   char *out,
                                   cx_sha3_t *sha3Context,
                                   uint64_t chainId);

void getEthAddressFromKey(cx_ecfp_public_key_t *publicKey, uint8_t *out, cx_sha3_t *sha3Context);

void getEthDisplayableAddress(uint8_t *in,
                              char *out,
                              size_t out_len,
                              cx_sha3_t *sha3,
                              uint64_t chainId);

bool adjustDecimals(char *src,
                    uint32_t srcLength,
                    char *target,
                    uint32_t targetLength,
                    uint8_t decimals);

bool uint256_to_decimal(const uint8_t *value, size_t value_len, char *out, size_t out_len);

void amountToString(const uint8_t *amount,
                    uint8_t amount_len,
                    uint8_t decimals,
                    const char *ticker,
                    char *out_buffer,
                    uint8_t out_buffer_size);

void u64_to_string(uint64_t src, char *dst, uint8_t dst_size);
