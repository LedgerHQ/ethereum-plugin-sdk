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

typedef struct nftInfo_t {
    uint8_t contractAddress[ADDRESS_LENGTH];  // must be first item
    char collectionName[COLLECTION_NAME_MAX_LEN + 1];
} nftInfo_t;

// TOKENS

#define MAX_TICKER_LEN 11  // 10 characters + '\0'

typedef struct tokenDefinition_t {
    uint8_t address[ADDRESS_LENGTH];  // must be first item
    char ticker[MAX_TICKER_LEN];
    uint8_t decimals;
} tokenDefinition_t;

// UNION

typedef union extraInfo_t {
    tokenDefinition_t token;
// Would have used HAVE_NFT_SUPPORT but it is only declared for the Ethereum app
// and not plugins
#ifndef TARGET_NANOS
    nftInfo_t nft;
#endif
} extraInfo_t;
// --8<-- [end:asset_info]
