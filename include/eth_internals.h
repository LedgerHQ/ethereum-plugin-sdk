/* This file is auto-generated, don't edit it */

#pragma once

#include <stdbool.h>
#include <string.h>
#include "os.h"
#include "cx.h"
#ifdef HAVE_NBGL
#include "nbgl_types.h"
#include "glyphs.h"
#endif

#define MAX_TICKER_LEN 11  // 10 characters + '\0'

#define ADDRESS_LENGTH 20

#define INT256_LENGTH  32

#define WEI_TO_ETHER 18

#define SELECTOR_SIZE    4

#define PARAMETER_LENGTH 32

#define RUN_APPLICATION 1

#define COLLECTION_NAME_MAX_LEN 70

typedef struct tokenDefinition_t {
    uint8_t address[ADDRESS_LENGTH];  // must be first item
#ifdef HAVE_CONTRACT_NAME_IN_DESCRIPTOR
    uint8_t contractName[ADDRESS_LENGTH];
#endif
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

typedef struct nftInfo_t {
    uint8_t contractAddress[ADDRESS_LENGTH];  // must be first item
    char collectionName[COLLECTION_NAME_MAX_LEN + 1];
} nftInfo_t;

typedef struct caller_app_t {
    const char *name;
#ifdef HAVE_NBGL
    const nbgl_icon_details_t *icon;
#endif
    char type;  // does not have to be set by the caller app
} caller_app_t;

typedef union extraInfo_t {
    tokenDefinition_t token;
    nftInfo_t nft;
} extraInfo_t;

static __attribute__((no_instrument_function)) inline int allzeroes(const void *buf, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    for (size_t i = 0; i < n; ++i) {
        if (p[i]) {
            return 0;
        }
    }
    return 1;
}

static const char HEXDIGITS[] = "0123456789abcdef";

bool getEthAddressStringFromBinary(uint8_t *address,
                                   char *out,
                                   cx_sha3_t *sha3Context,
                                   uint64_t chainId);

bool getEthAddressFromKey(cx_ecfp_public_key_t *publicKey, uint8_t *out, cx_sha3_t *sha3Context);

bool getEthDisplayableAddress(uint8_t *in,
                              char *out,
                              size_t out_len,
                              cx_sha3_t *sha3,
                              uint64_t chainId);

bool adjustDecimals(const char *src,
                    size_t srcLength,
                    char *target,
                    size_t targetLength,
                    uint8_t decimals);

bool uint256_to_decimal(const uint8_t* value, size_t value_len, char* out, size_t out_len);

bool amountToString(const uint8_t* amount,
                    uint8_t amount_len,
                    uint8_t decimals,
                    const char* ticker,
                    char* out_buffer,
                    size_t out_buffer_size);

bool u64_to_string(uint64_t src, char *dst, uint8_t dst_size);

void copy_address(uint8_t* dst, const uint8_t* parameter, uint8_t dst_size);

void copy_parameter(uint8_t* dst, const uint8_t* parameter, uint8_t dst_size);

bool U2BE_from_parameter(const uint8_t* parameter, uint16_t* value);

bool U4BE_from_parameter(const uint8_t* parameter, uint32_t* value);
