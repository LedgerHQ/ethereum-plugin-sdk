/* This file is auto-generated, don't edit it */

#pragma once

#include "os.h"
#include "cx.h"

#define MAX_TICKER_LEN 12  // 10 characters + ' ' + '\0'

#define ADDRESS_LENGTH 20

#define INT256_LENGTH 32

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
    CHAIN_KIND_THUNDERCORE
} chain_kind_t;

typedef struct tokenDefinition_t {
#ifdef HAVE_CONTRACT_NAME_IN_DESCRIPTOR
    uint8_t contractName[ADDRESS_LENGTH];
#endif
    uint8_t address[ADDRESS_LENGTH];
    uint8_t ticker[MAX_TICKER_LEN];
    uint8_t decimals;
} tokenDefinition_t;

typedef struct txInt256_t {
    uint8_t value[INT256_LENGTH];
    uint8_t length;
} txInt256_t;

typedef struct txContent_t {
    txInt256_t gasprice;
    txInt256_t startgas;
    txInt256_t value;
    txInt256_t nonce;
    uint8_t destination[ADDRESS_LENGTH];
    uint8_t destinationLength;
    uint8_t v[4];
    uint8_t vLength;
} txContent_t;

typedef struct chain_config_s {
    char coinName[10];  // ticker
    uint32_t chainId;
    chain_kind_t kind;
} chain_config_t;

void getEthAddressStringFromBinary(uint8_t *address,
                                   uint8_t *out,
                                   cx_sha3_t *sha3Context,
                                   chain_config_t *chain_config);
