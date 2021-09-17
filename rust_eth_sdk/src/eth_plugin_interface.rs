use cty;

pub const PLUGIN_ID_LENGTH: usize = 30;
pub const MAX_TICKER_LEN: usize = 12; // 10 characters + ' ' + '\0'
pub const ADDRESS_LENGTH: usize = 20;
pub const INT256_LENGTH: usize = 32;
pub const WEI_TO_ETHER: u8 = 18;
pub const SELECTOR_SIZE: u8 = 4;
pub const PARAMETER_LENGTH: usize = 32;

#[repr(u8)]
pub enum EthereumArg {
    RunApplication = 1,
}

/// Interface version. To be updated everytime we introduce breaking changes to the plugin interface.
#[repr(u8)]
pub enum PluginInterfaceVersion {
    Version1 = 1,
    Latest = 2,
}

#[repr(u16)]
pub enum PluginMsg {
    InitContract = 257,
    ProvideParameter = 258,
    Finalize = 259,
    ProvideToken = 260,
    QueryId = 261,
    QueryUi = 262,
    CheckPresence = 511,
}

#[repr(u8)]
pub enum PluginResult {
    Error = 0,
    Unavailable = 1,
    Unsuccesful = 2,
    Successful = 3,
    Ok = 4,
    OkAlias = 5,
    Fallback = 6,
}

#[repr(u8)]
pub enum UiType {
    AmountAddress = 1,
    Generic = 2,
}

#[repr(C)]
pub struct tokenDefinition_t {
    pub address: [u8; ADDRESS_LENGTH],
    pub ticker: [i8; MAX_TICKER_LEN],
    pub decimals: u8,
}

pub type PluginCall =
    ::core::option::Option<unsafe extern "C" fn(arg1: cty::c_int, arg2: *mut cty::c_void)>;

/// Shared objects, read-write
#[repr(C)]
struct PluginSharedRW {
    sha3: *mut cx_sha3_t,
}

#[repr(C)]
pub struct txInt256_t {
    pub value: [u8; INT256_LENGTH],
    pub length: u8,
}

#[repr(C)]
pub struct txContent_t {
    pub gasprice: txInt256_t,
    pub startgas: txInt256_t,
    pub value: txInt256_t,
    pub nonce: txInt256_t,
    pub chainID: txInt256_t,
    pub destination: [u8; ADDRESS_LENGTH],
    pub destinationLength: u8,
    pub v: [u8; 8usize],
    pub vLength: u8,
    pub dataPresent: bool,
}

/// Shared objects, read-only
#[repr(C)]
pub struct PluginSharedRO {
    pub txContent: *mut txContent_t,
}

/// Init Contract
#[repr(C)]
struct PluginInitContract {
    pub interfaceVersion: PluginInterfaceVersion,
    pub result: u8,

    // in
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,
    pub pluginContextLength: u32,
    pub selector: *mut u8, // 4 bytes selector
    pub dataSize: u32,

    pub alias: *mut i8, // 29 bytes alias if ETH_PLUGIN_RESULT_OK_ALIAS set
}

/// Provide parameter
#[repr(C)]
struct PluginProvideParameter {
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,
    pub parameter: *mut u8, // 32 bytes parameter
    pub parameterOffset: u32,
    pub result: u8,
}

/// Finalize
#[repr(C)]
struct PluginFinalize {
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,

    pub tokenLookup1: *mut u8, // set by the plugin if a token should be looked up
    pub tokenLookup2: *mut u8,

    pub amount: *mut u8,  // set an uint256 pointer if uiType is UI_AMOUNT_ADDRESS
    pub address: *mut u8, // set to the destination address if uiType is UI_AMOUNT_ADDRESS. Set to the
    // user's address if uiType is UI_TYPE_GENERIC
    pub uiType: UiType,
    pub numScreens: u8, // ignored if uiType is UI_AMOUNT_ADDRESS
    pub result: u8,
}

// If uiType is UI_AMOUNT_ADDRESS, the amount and address provided by the plugin will be used
// If tokenLookup1 is set, the amount is provided for this token

// if uiType is UI_TYPE_GENERIC, the ETH application provides tokens if requested then prompts
// for each UI field
// The first field is forced by the ETH app to be the name + version of the plugin handling the
// request The last field is the fee amount

// Provide token
#[repr(C)]
struct PluginProvideToken {
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,

    pub token1: *mut tokenDefinition_t, // set by the ETH application, to be saved by the plugin
    pub token2: *mut tokenDefinition_t,

    pub additionalScreens: u8, // Used by the plugin if it needs to display additional screens
    // based on the information received from the token definitions.
    pub result: u8,
}

// Query Contract name and version
// This is always called on the non aliased contract
#[repr(C)]
struct PluginQueryContractId {
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,

    pub name: *mut i8,
    pub nameLength: u32,
    pub version: *mut i8,
    pub versionLength: u32,

    pub result: u8,
}

// Query Contract UI
#[repr(C)]
struct PluginQueryContractUi {
    pub ethPluginSharedRW_t: *mut PluginSharedRW,
    pub ethPluginSharedRO_t: *mut PluginSharedRO,
    pub pluginContext: *mut u8,
    pub screenIndex: u8,
    pub title: *mut i8,
    pub titleLength: u32,
    pub msg: *mut i8,
    pub msgLength: u32,
    pub result: u8,
}
