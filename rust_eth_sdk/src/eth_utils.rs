use core::ops::Add;

use crate::eth_plugin_interface::{ADDRESS_LENGTH, INT256_LENGTH};

#[derive(Default, PartialEq, Eq)]
pub struct Address([u8; ADDRESS_LENGTH]);

impl From<*const u8> for Address {
    fn from(_: *const u8) -> Self {
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
    fn to_amount(&self, dst: &mut str, ticker: &str, decimals: u8) {
        // We could use a simple `amountToString` if we create the bindings
        // need to be careful because ticker is not necessarily null terminated?
        // need to transformer ticker and dst to Cstrings...
        // amountToString(self.0, self.0.len(), decimals, ticker, dst, dst.len());
        unimplemented!()
    }

    fn to_str(&self, dst: &mut str) {
        // We could use `uint256_to_decimal` if we create the bindings
        // need to transform dst to Cstring...
        // uint256_to_decimal(self.0, self.0.len(), dst, dst.len())
        unimplemented!()
    }

    // We should implem add, sub, multiply
}
