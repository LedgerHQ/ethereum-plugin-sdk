/*******************************************************************************
 *   Ledger Ethereum App
 *   (c) 2016-2019 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <stdint.h>
#include "common_utils.h"

// --8<-- [start:asset_info]
// NFT

#define COLLECTION_NAME_MAX_LEN 70

typedef struct {
    char collection_name[COLLECTION_NAME_MAX_LEN + 1];
} nft_info_t;

// TOKENS

#define MAX_TICKER_LEN 10

typedef struct {
    char ticker[MAX_TICKER_LEN + 1];
    uint8_t decimals;
} token_info_t;

typedef enum {
    ASSET_NFT,
    ASSET_TOKEN,
} asset_type_t;

typedef struct {
    asset_type_t type;
    uint64_t chain_id;
    uint8_t address[ADDRESS_LENGTH];
    union {
        token_info_t token;
// Would have used HAVE_NFT_SUPPORT but it is only declared for the Ethereum app
// and not plugins
#ifndef TARGET_NANOS
        nft_info_t nft;
#endif
    };
} asset_info_t;
// --8<-- [end:asset_info]
