/*****************************************************************************
 *   Ledger
 *   (c) 2023 Ledger SAS
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
 *****************************************************************************/

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "eth_plugin_interface.h"

// --8<-- [start:plugin_utils]
// Size of a selector in bytes
#define SELECTOR_SIZE 4

// Length of a parameter in bytes
#define PARAMETER_LENGTH 32

/**
 * @brief Copies a portion of the parameter data to the destination buffer,
 * aligning the copy to the end.
 *
 * This function copies bytes from the `parameter` array to the `dst` buffer.
 * The number of bytes copied is determined by the smaller of `dst_size` and
 * `ADDRESS_LENGTH`. The copy starts from the end of the `parameter` array.
 *
 * @param dst A pointer to the destination buffer where the data will be copied.
 * @param parameter A pointer to the source data array.
 * @param dst_size The size of the destination buffer.
 */
void copy_address(uint8_t *dst, const uint8_t *parameter, uint8_t dst_size);

/**
 * @brief Copies a portion of the parameter data to the destination buffer.
 *
 * This function copies bytes from the `parameter` array to the `dst` buffer.
 * The number of bytes copied is determined by the smaller of `dst_size` and
 * `PARAMETER_LENGTH`.
 *
 * @param dst A pointer to the destination buffer where the data will be copied.
 * @param parameter A pointer to the source data array.
 * @param dst_size The size of the destination buffer.
 */
void copy_parameter(uint8_t *dst, const uint8_t *parameter, uint8_t dst_size);

/**
 * @brief Extracts a 16-bit unsigned integer from the parameter data if the rest
 * of the data is zero.
 *
 * This function checks if all bytes, except for the last 2 bytes of the
 * `parameter` array, are zero. If so, it extracts a 16-bit unsigned integer
 * from the end of the `parameter` array (in big-endian format) and stores it in
 * `value`.
 *
 * @param parameter A pointer to the parameter data array.
 * @param value A pointer to a 16-bit unsigned integer where the extracted value
 * will be stored.
 * @return true if the extraction was successful, false otherwise.
 */
bool U2BE_from_parameter(const uint8_t *parameter, uint16_t *value);

/**
 * @brief Extracts a 32-bit unsigned integer from the parameter data if the rest
 * of the data is zero.
 *
 * This function checks if all bytes, except for the last 4 bytes of the
 * `parameter` array, are zero. If so, it extracts a 32-bit unsigned integer
 * from the end of the `parameter` array (in big-endian format) and stores it in
 * `value`.
 *
 * @param parameter A pointer to the parameter data array.
 * @param value A pointer to a 32-bit unsigned integer where the extracted value
 * will be stored.
 * @return true if the extraction was successful, false otherwise.
 */
bool U4BE_from_parameter(const uint8_t *parameter, uint32_t *value);

/**
 * @brief Finds the index of a selector value in an array.
 *
 * This function searches for a specific selector value within an `array` of
 * `size` elements. If the selector is found, its index is stored in `idx` (if
 * not NULL), and the function returns true. Otherwise, it returns false.
 *
 * @param selector The value to search for in the array.
 * @param array A pointer to the array of selector values.
 * @param size The number of elements in the array.
 * @param idx A pointer to a size_t variable where the index of the found
 * selector will be stored (if not NULL).
 * @return true if the selector was found, false otherwise.
 */
bool find_selector(uint32_t selector,
                   const uint32_t *array,
                   size_t size,
                   size_t *idx);
// --8<-- [end:plugin_utils]
