#pragma once

#include "os.h"
#include "cx.h"

// Include other header compatible with plugins
#include "asset_info.h"
#include "caller_api.h"
#include "common_utils.h"
#include "plugin_utils.h"
#include "tx_content.h"
#include "bip32_utils.h"

/*************************************************************************************************
 * Comments provided in this file are quick reminders on the usage of the plugin interface       *
 * Reading the real plugin documentation is GREATLY recommended.                                 *
 * You can find the latest version here:                                                         *
 * https://ethereum-plugin-sdk.ledger.com/                                                       *
 *************************************************************************************************/

// Interface version. Will be updated every time a breaking change in the
// interface is introduced.
typedef enum eth_plugin_interface_version_e {
    ETH_PLUGIN_INTERFACE_VERSION_1 = 1,
    ETH_PLUGIN_INTERFACE_VERSION_2 = 2,
    ETH_PLUGIN_INTERFACE_VERSION_3 = 3,
    ETH_PLUGIN_INTERFACE_VERSION_4 = 4,
    ETH_PLUGIN_INTERFACE_VERSION_5 = 5,
    ETH_PLUGIN_INTERFACE_VERSION_6 = 6,
    ETH_PLUGIN_INTERFACE_VERSION_LATEST = 7,
} eth_plugin_interface_version_t;

// Codes for the different requests Ethereum can send to the plugin
// The dispatch is handled by the SDK itself, the plugin code does not have to
// handle it
typedef enum eth_plugin_msg_e {
    // Codes for actions the Ethereum app can ask the plugin to perform
    ETH_PLUGIN_INIT_CONTRACT = 0x0101,
    ETH_PLUGIN_PROVIDE_PARAMETER = 0x0102,
    ETH_PLUGIN_FINALIZE = 0x0103,
    ETH_PLUGIN_PROVIDE_INFO = 0x0104,
    ETH_PLUGIN_QUERY_CONTRACT_ID = 0x0105,
    ETH_PLUGIN_QUERY_CONTRACT_UI = 0x0106,

    // Special request: the Ethereum app is checking if we are installed on the
    // device
    ETH_PLUGIN_CHECK_PRESENCE = 0x01FF,
} eth_plugin_msg_t;

// Reply codes when responding to the Ethereum application
typedef enum eth_plugin_result_e {
    // Unsuccessful return values
    ETH_PLUGIN_RESULT_ERROR = 0x00,
    ETH_PLUGIN_RESULT_UNAVAILABLE = 0x01,
    ETH_PLUGIN_RESULT_UNSUCCESSFUL = 0x02,  // Used for comparison

    // Successful return values
    ETH_PLUGIN_RESULT_SUCCESSFUL = 0x03,  // Used for comparison
    ETH_PLUGIN_RESULT_OK = 0x04,
    ETH_PLUGIN_RESULT_FALLBACK = 0x06,
} eth_plugin_result_t;

// Format of UI the Ethereum application has to use for this plugin
typedef enum eth_ui_type_e {
    // If uiType is UI_AMOUNT_ADDRESS, Ethereum will use the amount/address UI
    // the amount and address provided by the plugin will be used
    // If tokenLookup1 is set, the amount is provided for this token
    ETH_UI_TYPE_AMOUNT_ADDRESS = 0x01,

    // If uiType is UI_TYPE_GENERIC, Ethereum will use the dedicated ETH plugin
    // UI
    // the ETH application provides tokens if requested then prompts for each UI
    // field
    // The first field is forced by the ETH app to be the name + version of the
    // plugin handling the
    // request. The last field is the fee amount
    ETH_UI_TYPE_GENERIC = 0x02,
} eth_ui_type_t;

// --8<-- [start:plugin_context]
// Plugin-only memory allocated by the Ethereum application and used by the
// plugin. 1k memory is available.
#define PLUGIN_CONTEXT_SIZE (32 * INT256_LENGTH)
// --8<-- [end:plugin_context]
// It is recommended to cast the raw uin8_t array to a structure meaningful for
// your plugin

// Helper to check that the actual plugin context structure is not bigger than
// the allocated memory
#define ASSERT_SIZEOF_PLUGIN_CONTEXT(s)              \
    _Static_assert(sizeof(s) <= PLUGIN_CONTEXT_SIZE, \
                   "Plugin context structure is too big.")

/*
 * HANDLERS AND PARAMETERS
 * Parameters associated with the requests the Ethereum application can ask the
 * plugin to perform The plugin SDK will automatically call the relevant handler
 * for the received code, so the plugin has to define each of the handler
 * functions declared below.
 */

/*
 --8<-- [start:handle_init_contract_explanation]
The Ethereum application will call the plugin using this handle upon reception
of a smart contract that the plugin is supposed to know how to parse.

The plugin needs to perform the following actions:

- Check that the selector is recognized
- Initialize the fields of its context structure

Most of this logic is already done in the boilerplate plugin. You just need to
adapt for your use case.
--8<-- [end:handle_init_contract_explanation]
*/

// --8<-- [start:handle_init_contract_parameters]
typedef struct ethPluginInitContract_s {
    // ===== READ ONLY ===== //
    // INPUT. Used to check that `ETH_PLUGIN_INTERFACE_VERSION_LATEST` is
    // correct.
    eth_plugin_interface_version_t interfaceVersion;

    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;

    // INPUT. Size of context allocated by the Ethereum application, must be
    // equal to PLUGIN_CONTEXT_SIZE.
    size_t pluginContextLength;

    // INPUT. Selector of the smart contract that Ethereum application is asking
    // te plugin to display.
    const uint8_t *selector;

    // INPUT. Total length of the data to come.
    size_t dataSize;
    bip32_path_t *bip32;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext;

    // ===== WRITE ONLY ===== //
    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    // - ETH_PLUGIN_RESULT_FALLBACK : if the signing logic should fallback to
    // the generic one
    eth_plugin_result_t result;

} ethPluginInitContract_t;
// --8<-- [end:handle_init_contract_parameters]

/*
 --8<-- [start:handle_provide_parameter_explanation]
The Ethereum application will call the plugin repeatidly using this handle to
feed it the entire smart contract data parameter by parameter.

The plugin needs to perform the following actions:

- Read all parameters and keep track of the smart contract parsing progression
- Check that the values received are valid/possible when applicable
- Store in the context the data that will need to be displayed on screen.
- Report an error to the ethereum application if the smart contract has an
issue.

An example of smart contract parsing is already done in the boilerplate plugin.
Adapt and expand it for your use case.
--8<-- [end:handle_provide_parameter_explanation]
*/

// --8<-- [start:handle_provide_parameter_parameters]
typedef struct ethPluginProvideParameter_s {
    // ===== READ ONLY ===== //
    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;

    // INPUT. Pointer to the 32 bytes parameter being parsed in the smart
    // contract data.
    const uint8_t *parameter;

    // INPUT. Offset to this parameter from the beginning of the data field
    // (starts at 4, following the selector).
    uint32_t parameterOffset;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext; // PLUGIN_CONTEXT_SIZE

    // ===== WRITE ONLY ===== //
    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    // - ETH_PLUGIN_RESULT_FALLBACK : if the signing logic should fallback to
    // the generic one
    eth_plugin_result_t result;

    // INPUT. Size of the parameter, usually 32 but can also be less for the
    // last one.
    uint8_t parameter_size;
} ethPluginProvideParameter_t;
// --8<-- [end:handle_provide_parameter_parameters]

/*
 --8<-- [start:handle_finalize_explanation]
The Ethereum application will call this handle when the entire smart contract
has been fed to the plugin using the provide_parameter handle.

The plugin needs to perform the following actions:

- Check that nothing is missing from the smart contract if applicable.
- Report an error to the ethereum application if the smart contract has an
issue.
- Request information about a ERC20 token if needed (2 max).
- Set the UI layout to SIMPLIFIED (called `UI_AMOUNT_ADDRESS`) or CUSTOM (called
`ETH_UI_TYPE_GENERIC`)
    - CUSTOM: Inform the Ethereum application of the number of screens needed to
display the smart contract.
    - SIMPLIFIED: Inform the Ethereum application of the amount and address to
display.

An example of smart contract parsing finalization is already done in the
boilerplate plugin. Adapt and expand it for your use case.
--8<-- [end:handle_finalize_explanation]
*/

// --8<-- [start:handle_finalize_parameters]
typedef struct ethPluginFinalize_s {
    // ===== READ ONLY ===== //
    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext; // PLUGIN_CONTEXT_SIZE

    // ===== WRITE ONLY ===== //
    // OUTPUT. The plugin can set this value to a 20 bytes array in
    // pluginContext containing the address of an ERC20 token. In this case
    // Ethereum will call the plugin with handle_provide_token() with the
    // requested ERC20 token information. The Ethereum application must be made
    // aware of ERC20 token information first using 'PROVIDE ERC 20 TOKEN
    // INFORMATION' APDU. Leave the value at NULL if not needed
    const uint8_t *tokenLookup1;
    // OUTPUT. Same as tokenLookup1.
    const uint8_t *tokenLookup2;
    // Reminder: const applies to the pointed memory area, which means the plugin
    // can set the value and ethereum will modify the pointed value.

    // OUTPUT. The plugin needs to set this value to either
    // ETH_UI_TYPE_AMOUNT_ADDRESS for an amount/address UI or
    // ETH_UI_TYPE_GENERIC for a generic UI.
    eth_ui_type_t uiType;
    union {
        // OUTPUT. The plugin needs to set this pointer to a 256 bits number in
        // pluginContext to display as the amount in UI_AMOUNT_ADDRESS case.
        // IGNORED if uiType is UI_TYPE_GENERIC.
        const uint8_t *amount;
        // OUTPUT. The plugin needs to set this value to the number of screens
        // needed to display the smart contract in ETH_UI_TYPE_GENERIC case.
        // IGNORED if uiType is UI_AMOUNT_ADDRESS.
        uint8_t numScreens;
    };
    // OUTPUT. The plugin needs to set this pointer to a 20 bytes address in
    // pluginContext to display as the address in UI_AMOUNT_ADDRESS case.
    // Set to the user's address if uiType is UI_TYPE_GENERIC
    const uint8_t *address;  // set a pointer to the destination address (in pluginContext) if uiType is UI_AMOUNT_ADDRESS.

    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    // - ETH_PLUGIN_RESULT_FALLBACK : if the signing logic should fallback to
    // the generic one
    eth_plugin_result_t result;

} ethPluginFinalize_t;
// --8<-- [end:handle_finalize_parameters]

/*
 --8<-- [start:handle_provide_token_explanation]
The Ethereum application will call this handle when the plugin has requested
ERC20 token information in `handle_finalize`

The plugin needs to perform the following actions:

- Check that provided token matches the one requested.
- Increase the number of screens needed for the display if needed.
- Report an error to the ethereum application if the display must be aborted.

!!! warning
    The Ethereum application can only provide to the plugin information about
    ERC20 token it knows about.<br/>
    You need to provide the ERC20 token information to the Ethereum application
    using `PROVIDE ERC 20 TOKEN INFORMATION` APDU.

An example of token info providing is already done in the boilerplate plugin.
Adapt and expand it for your use case.
--8<-- [end:handle_provide_token_explanation]
*/

// --8<-- [start:handle_provide_token_parameters]
typedef struct ethPluginProvideInfo_s {
    // ===== READ ONLY ===== //
    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;

    // INPUT. ERC20 token information as requested by tokenLookup1 in
    // handle_finalize. NULL if not found.
    union extraInfo_t *item1;
    // INPUT. Same as item1 but for tokenLookup2.
    union extraInfo_t *item2;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext; // PLUGIN_CONTEXT_SIZE

    // ===== WRITE ONLY ===== //
    // OUTPUT. Set by the plugin if it needs to display additional screens based
    // on the information received from the token definitions.
    uint8_t additionalScreens;  // Used by the plugin if it needs to display additional screens
                                // based on the information received from the token definitions.

    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    // - ETH_PLUGIN_RESULT_FALLBACK : if the signing logic should fallback to
    // the generic one
    eth_plugin_result_t result;

} ethPluginProvideInfo_t;
// --8<-- [end:handle_provide_token_parameters]

/*
 --8<-- [start:handle_query_contract_id_explanation]
The Ethereum application will call this handle to query the contract name and
version to display.

The plugin needs to perform the following actions:

- Write the name of the plugin/smart contract
- Write the version

An example is already done in the boilerplate plugin. Adapt and expand it for
your use case.
--8<-- [end:handle_query_contract_id_explanation]
*/

// --8<-- [start:handle_query_contract_id_parameters]
typedef struct ethQueryContractID_s {
    // ===== READ ONLY ===== //
    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;
    // INPUT. Maximum possible name string length
    size_t nameLength;
    // INPUT. Maximum possible version string length
    size_t versionLength;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext; // PLUGIN_CONTEXT_SIZE

    // ===== WRITE ONLY ===== //
    // OUTPUT. Pointer to the name of the plugin
    char *name;
    // OUTPUT. Pointer to the version of the plugin
    char *version;

    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    eth_plugin_result_t result;

} ethQueryContractID_t;
// --8<-- [end:handle_query_contract_id_parameters]

/*
 --8<-- [start:handle_query_contract_ui_explanation]
The Ethereum application will call this handle for each screen to display if a
custom UI was requested.

The plugin needs to perform the following actions:

- Write the screen title for the current screen index
- Write the screen content for the current screen index

An example is already done in the boilerplate plugin. Adapt and expand it for
your use case.
--8<-- [end:handle_query_contract_ui_explanation]
*/

// --8<-- [start:handle_query_contract_ui_parameters]
typedef struct ethQueryContractUI_s {
    // ===== READ ONLY ===== //
    // INPUT. Transaction data available to the plugin. READ-ONLY.
    const txContent_t *txContent;

    // INPUT. ERC20 token information as requested by tokenLookup1 in
    // handle_finalize. NULL if not found.
    union extraInfo_t *item1;
    // INPUT. Same as item1 but for tokenLookup2.
    union extraInfo_t *item2;

    // INPUT. String that holds the network ticker
    char network_ticker[MAX_TICKER_LEN];

    // INPUT. Current screen to display.
    uint8_t screenIndex;
    // INPUT. Maximum possible title length
    size_t titleLength;
    // INPUT. Maximum possible msg length
    size_t msgLength;

    // ===== READ WRITE ===== //
    // RW INPUT. Contains the semi-persistent RAM space that can be used by the
    // plugin in each handle call.
    uint8_t *pluginContext; // PLUGIN_CONTEXT_SIZE

    // ===== WRITE ONLY ===== //
    // OUTPUT. Pointer to the first line of the screen, to be filled by the
    // plugin
    char *title;
    // OUTPUT. Pointer to the second line of he screen, to be filled by the
    // plugin
    char *msg;

    // OUTPUT. Used by the plugin to inform the Ethereum application of the
    // result of this handle The following return codes are expected, any other
    // will abort the signing process:
    // - ETH_PLUGIN_RESULT_OK
    eth_plugin_result_t result;

} ethQueryContractUI_t;
// --8<-- [end:handle_query_contract_ui_parameters]

// Don't define the handlers when compiling the Ethereum application
#ifndef IS_NOT_A_PLUGIN
// --8<-- [start:handlers_functions]
// Functions to implement in the plugin
void handle_init_contract(ethPluginInitContract_t *parameters);
void handle_provide_parameter(ethPluginProvideParameter_t *parameters);
void handle_finalize(ethPluginFinalize_t *parameters);
void handle_provide_token(ethPluginProvideInfo_t *parameters);
void handle_query_contract_id(ethQueryContractID_t *parameters);
void handle_query_contract_ui(ethQueryContractUI_t *parameters);
// --8<-- [end:handlers_functions]
#endif
