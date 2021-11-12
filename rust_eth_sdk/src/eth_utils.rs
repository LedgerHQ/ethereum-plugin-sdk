use core::ops::Add;

use crate::eth_plugin_interface::{ADDRESS_LENGTH, INT256_LENGTH};

#[derive(Default, PartialEq, Eq)]
pub struct Address([u8; ADDRESS_LENGTH]);

impl From<*const u8> for Address {
    fn from(_: *const u8) -> Self {
        unimplemented!();
    }
}

impl Address {
    /// Transforms the address to a string prefixed with 0x (e.g. 0xa123b....);
    pub fn to_str(&self, dst: *mut u8, dst_len: u8) {
        unimplemented!();
    }
}

#[derive(Default)]
pub struct Number([u8; INT256_LENGTH]);

impl From<*const u8> for Number {
    fn from(_: *const u8) -> Self {
        unimplemented!();
    }
}

impl Number {
    /// Transforms the number to a string that is prefixed with the ticker and decimal adjusted, e.g.
    /// `ETH 1.337` and copies it to `dst`.
    pub fn to_amount(&self, dst: *mut u8, dst_len: u8, ticker: &str, decimals: u8) {
        // We could use a simple `amountToString` if we create the bindings
        // need to be careful because ticker is not necessarily null terminated?
        // amountToString(self.0.as_ptr(), self.0.len(), decimals, ticker.as_ptr(), dst, dst_len);
        unimplemented!()
    }

    /// Transforms the number to its string representation and copies the string to `dst`.
    pub fn to_str(&self, dst: *mut u8, dst_len: u8) {
        // We could use `uint256_to_decimal` if we create the bindings
        // need to transform dst to Cstring ?
        // uint256_to_decimal(self.0.as_ptr(), self.0.len(), dst, dst_len)
        unimplemented!()
    }

    // We should implem add, sub, multiply
}
