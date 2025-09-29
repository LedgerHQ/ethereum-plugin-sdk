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

#include <stddef.h>
#include <stdint.h>

#include "cx.h"
#include "format.h"
#include "os.h"

// --8<-- [start:common_utils]

// Number of decimal places in 1 Ether (or similar cryptocurrency) when
// represented in Wei.
#define WEI_TO_ETHER 18

// The standard length of an Ethereum address
#define ADDRESS_LENGTH 20

// The length of a 128-bit integer in bytes
#define INT128_LENGTH 16

// The length of a 256-bit integer in bytes.
#define INT256_LENGTH 32

// The byte size of a Keccak-256 hash.
#define KECCAK256_HASH_BYTESIZE 32

// Hexadecimal digits for formatting and parsing purposes.
static const char HEXDIGITS[] = "0123456789abcdef";

// Computes the number of elements in an array.
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/**
 * @brief Converts a binary value to a hexadecimal string representation.
 *
 * This function formats a binary value (represented by `value`) into a
 * hexadecimal string, prefixed with '0x'. The resulting string is stored in the
 * `out` buffer. The buffer should be large enough to accommodate the '0x'
 * prefix and the hexadecimal representation of the binary value.
 *
 * @param out A pointer to the buffer where the hexadecimal string will be
 * stored.
 * @param outl The length of the output buffer.
 * @param value A pointer to the binary value to be converted.
 * @param len The length of the binary value.
 * @return 0 on success, or -1 if an error occurs (e.g., buffer too small).
 */
int array_bytes_string(char *out, size_t outl, const void *value, size_t len);

/**
 * @brief Converts a big-endian byte array to a 64-bit unsigned integer.
 *
 * This function interprets the byte array `in` as a big-endian number and
 * converts it to a 64-bit unsigned integer. The conversion stops after `size`
 * bytes or when the input array has been fully processed.
 *
 * @param in A pointer to the byte array representing the big-endian number.
 * @param size The number of bytes to consider from the byte array.
 * @return The 64-bit unsigned integer representation of the byte array.
 */
uint64_t u64_from_BE(const uint8_t *in, uint8_t size);

/**
 * @brief Converts a 64-bit unsigned integer to a string.
 *
 * This function converts a 64-bit unsigned integer (`src`) to its decimal
 * string representation, storing the result in the `dst` buffer. The conversion
 * ensures that the resulting string is null-terminated and the buffer size
 * (`dst_size`) is sufficient to hold the result and the null terminator.
 *
 * @param src The 64-bit unsigned integer to convert.
 * @param dst A pointer to the buffer where the decimal string will be stored.
 * @param dst_size The size of the output buffer.
 * @return true if the conversion was successful and the output buffer contains
 * the resulting string, false if the buffer is too small or an error occurs.
 */
bool u64_to_string(uint64_t src, char *dst, uint8_t dst_size);

/**
 * @brief Converts a uint256 value to its decimal string representation.
 *
 * This function takes a uint256 value represented as a byte array, converts it
 * to a decimal string, and stores the result in the provided `out` buffer.
 * Leading zeros in the resulting decimal string are removed.
 *
 * @param value A pointer to the byte array representing the uint256 value.
 * @param value_len The length of the byte array `value`.
 * @param out A pointer to the buffer where the decimal string representation
 * will be stored.
 * @param out_len The length of the output buffer `out`.
 */
bool uint256_to_decimal(const uint8_t *value,
                        size_t value_len,
                        char *out,
                        size_t out_len);

/**
 * @brief Converts an amount to its string representation with decimals and
 * ticker.
 *
 * This function takes a numeric amount represented as a byte array, converts it
 * to a decimal string, adjusts its decimal position according to the specified
 * number of decimals, and appends a ticker. The result is stored in the
 * `out_buffer`.
 *
 * @param amount A pointer to the byte array representing the amount.
 * @param amount_size The size of the amount byte array.
 * @param decimals The number of decimals to adjust to.
 * @param ticker A pointer to the ticker string to append to the amount.
 * @param out_buffer A pointer to the buffer where the resulting string will be
 * stored.
 * @param out_buffer_size The size of the output buffer.
 * @return true if the conversion and formatting were successful, false if the
 * output buffer is too small or an error occurs.
 */
bool amountToString(const uint8_t *amount,
                    uint8_t amount_len,
                    uint8_t decimals,
                    const char *ticker,
                    char *out_buffer,
                    size_t out_buffer_size);

/**
 * @brief Adjusts the decimal position of a numeric string based on a specified
 * number of decimals.
 *
 * This function takes a numeric string `src` and adjusts its decimal position
 * according to the specified number of `decimals`, storing the result in the
 * `target` buffer. If the `src` string is shorter than the number of decimals,
 * leading zeros are added. Trailing zeros are removed from the result.
 *
 * @param src A pointer to the source numeric string.
 * @param srcLength The length of the source string.
 * @param target A pointer to the buffer where the adjusted string will be
 * stored.
 * @param targetLength The length of the target buffer.
 * @param decimals The number of decimals to adjust to.
 * @return true if the adjustment was successful and the target buffer contains
 * the resulting string, false if the target buffer is too small or an error
 * occurs.
 */
bool adjustDecimals(const char *src,
                    size_t srcLength,
                    char *target,
                    size_t targetLength,
                    uint8_t decimals);

/**
 * @brief Computes the Ethereum address from a raw public key.
 *
 * This function takes a 65-byte raw public key, computes its Keccak-256 hash,
 * and extracts the last 20 bytes as the Ethereum address.
 *
 * @param raw_pubkey A pointer to the raw public key (65 bytes).
 * @param out A pointer to the buffer where the 20-byte Ethereum address will be
 * stored.
 */
void getEthAddressFromRawKey(const uint8_t raw_pubkey[static 65],
                             uint8_t out[static ADDRESS_LENGTH]);

/**
 * @brief Converts a raw public key to its Ethereum address string
 * representation.
 *
 * This function takes a 65-byte raw public key, computes its Keccak-256 hash,
 * extracts the last 20 bytes as the Ethereum address, and converts it to a
 * hexadecimal string with EIP-55 checksum, supporting EIP-1191 checksumming for
 * specific chain IDs.
 *
 * @param raw_pubkey A pointer to the raw public key (65 bytes).
 * @param out A pointer to the buffer where the checksum string representation
 * will be stored. The buffer must be at least (ADDRESS_LENGTH * 2) + 1 bytes
 * long.
 * @param chainId The chain ID to be used for EIP-1191 checksum (if applicable).
 */
void getEthAddressStringFromRawKey(const uint8_t raw_pubkey[static 65],
                                   char out[static(ADDRESS_LENGTH * 2) + 1],
                                   uint64_t chainId);

/**
 * @brief Converts a binary Ethereum address to its checksum string
 * representation.
 *
 * This function converts a binary Ethereum address to a hexadecimal string with
 * EIP-55 checksum. It supports EIP-1191 checksumming for specific chain IDs.
 *
 * @param address A pointer to the binary Ethereum address (20 bytes).
 * @param out A pointer to the buffer where the checksum string representation
 * will be stored. The buffer must be at least (ADDRESS_LENGTH * 2) + 1 bytes
 * long.
 * @param chainId The chain ID to be used for EIP-1191 checksum (if applicable).
 * @return true if the conversion was successful and the output buffer contains
 * the resulting string, false if an error occurs.
 */
bool getEthAddressStringFromBinary(const uint8_t *address,
                                   char out[static(ADDRESS_LENGTH * 2) + 1],
                                   uint64_t chainId);

/**
 * @brief Converts a binary Ethereum address to its lowercase string
 * representation.
 *
 * This function takes an Ethereum public key in binary format, converts it to a
 * lowercase hexadecimal string, and stores the result in the provided `out`
 * buffer. The resulting string will be null-terminated.
 *
 * @param in A pointer to the binary Ethereum public key.
 * @param out A pointer to the buffer where the lowercase string representation
 * will be stored. The buffer must be at least 43 bytes long.
 * @param out_len The length of the output buffer `out`.
 * @param chainId The chain ID to be used (for future compatibility or other
 * uses).
 * @return true if the conversion was successful and the output buffer contains
 * the resulting string, false if the output buffer is too small or an error
 * occurs.
 *
 * @example
 * uint8_t*:0xb47e3cd837dDF8e4c57F05d70Ab865de6e193BBB ->
 *      char*:"0xb47e3cd837dDF8e4c57F05d70Ab865de6e193BBB\0"
 */
bool getEthDisplayableAddress(const uint8_t *in,
                              char *out,
                              size_t out_len,
                              uint64_t chainId);

/**
 * @brief Checks if a buffer is entirely filled with zeroes.
 *
 * This function examines the first `n` bytes of the buffer pointed to by `buf`
 * to determine if all bytes are zero.
 *
 * @param buf A pointer to the buffer to be checked.
 * @param n The number of bytes to check in the buffer.
 * @return 1 if all bytes in the buffer are zero, 0 otherwise.
 */
int allzeroes(const void *buf, size_t n);

/**
 * @brief Checks if a buffer is entirely filled with the maximum byte value
 * (0xff).
 *
 * This function examines the first `n` bytes of the buffer pointed to by `buf`
 * to determine if all bytes are equal to 0xff.
 *
 * @param buf A pointer to the buffer to be checked.
 * @param n The number of bytes to check in the buffer.
 * @return 1 if all bytes in the buffer are 0xff, 0 otherwise.
 */
int ismaxint(const uint8_t *buf, int n);

/**
 * @deprecated
 * See format_hex in main SDK
 */
DEPRECATED static inline void array_hexstr(char *strbuf,
                                           const void *bin,
                                           unsigned int len) {
    // Consider the output buffer is sufficiently large!
    format_hex(bin, len, strbuf, (2 * len + 1));
}

// --8<-- [end:common_utils]
