use crate::eth_plugin_interface::{ADDRESS_LENGTH, INT256_LENGTH};

#[derive(Default, PartialEq, Eq)]
pub struct Address([u8; ADDRESS_LENGTH]);

#[derive(Default)]
pub struct Number([u8; INT256_LENGTH]);

impl Number {
    fn to_amount(&self, dst: &mut str, ticker: &str, decimals: u8) {}

    fn to_str(&self, dst: &str) {}

    // We should implem add, sub, multiply
}
