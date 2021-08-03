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

typedef enum chain_kind_e {
    CHAIN_KIND_ETHEREUM,
    CHAIN_KIND_ETHEREUM_CLASSIC,
    CHAIN_KIND_EXPANSE,
    CHAIN_KIND_POA,
    CHAIN_KIND_RSK,
    CHAIN_KIND_UBIQ,
    CHAIN_KIND_WANCHAIN,
    CHAIN_KIND_KUSD,
    CHAIN_KIND_PIRL,
    CHAIN_KIND_AKROMA,
    CHAIN_KIND_MUSICOIN,
    CHAIN_KIND_CALLISTO,
    CHAIN_KIND_ETHERSOCIAL,
    CHAIN_KIND_ELLAISM,
    CHAIN_KIND_ETHER1,
    CHAIN_KIND_ETHERGEM,
    CHAIN_KIND_ATHEIOS,
    CHAIN_KIND_GOCHAIN,
    CHAIN_KIND_MIX,
    CHAIN_KIND_REOSC,
    CHAIN_KIND_HPB,
    CHAIN_KIND_TOMOCHAIN,
    CHAIN_KIND_TOBALABA,
    CHAIN_KIND_DEXON,
    CHAIN_KIND_VOLTA,
    CHAIN_KIND_EWC,
    CHAIN_KIND_ARTIS_SIGMA1,
    CHAIN_KIND_ARTIS_TAU1,
    CHAIN_KIND_WEBCHAIN,
    CHAIN_KIND_THUNDERCORE,
    CHAIN_KIND_FLARE,
    CHAIN_KIND_THETA,
    CHAIN_KIND_BSC
} chain_kind_t;

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
    uint8_t v[4];
    uint8_t vLength;
    bool dataPresent;
} txContent_t;

typedef struct chain_config_s {
    char coinName[10];  // ticker
    uint32_t chainId;
    chain_kind_t kind;
} chain_config_t;

__attribute__((no_instrument_function)) inline int allzeroes(void *buf, size_t n) {
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
                                   chain_config_t *chain_config);

void getEthAddressFromKey(cx_ecfp_public_key_t *publicKey, uint8_t *out, cx_sha3_t *sha3Context);

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
