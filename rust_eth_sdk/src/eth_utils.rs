use crate::eth_plugin_interface::{ADDRESS_LENGTH, INT256_LENGTH};

pub struct Address([u8; ADDRESS_LENGTH]);

pub struct Number([u8; INT256_LENGTH]);

#[derive(Default)]
pub struct Amount([u8; INT256_LENGTH]);

impl Amount {
    fn displayable(&self, dst: &str, ticker: &str, decimals: u8) {}
}
