# Ethereum plugin documentation

This documentation will help you design your own ethereum plugin.

## What is a plugin?

A plugin is a lightweight application that only performs smart contract parsing and leverages the Ethereum application for the rest.

Your plugin will allow your users to clear-sign your smart contracts when using a Ledger device.

Plugins are designed to work hand-in-hand with the Ethereum application:

- The plugin handle the smart contract parsing
- The Ethereum application handles everything else (APDU reception, signature, screen management, bluetooth, etc)

Upon your smart contract reception, the Ethereum application will call your plugin to query the elements to display and your plugin will be responsible for:

- Extracting the relevant information from the smart contract.
- Replying the string to be displayed back to the Ethereum App.

## Coding my own plugin

### Use the Ethereum Plugin SDK

Use the Ledger developed [Ethereum Plugin SDK](https://github.com/LedgerHQ/ethereum-plugin-sdk).<br/>
The SDK will do all the busy work of your plugin and leave you with only a few handlers to code.<br/>
The SDK is designed to be used as a git submodule.

!!! note
    Always keep your SDK up to date with its **develop** branch.<br/>
    We are providing a CI workflow to help you check that the latest version is being used.

### Fork the Plugin Boilerplate

While starting a new plugin application from a blank repository + the SDK is technically possible, it is not *at all* recommended and support would not be provided.<br/>
Instead, fork our official template application [Plugin Boilerplate](https://github.com/LedgerHQ/app-plugin-boilerplate) and start from there.

You will start with a correct build structure, examples of handlers, our test framework working, and the CI workflows already setup.

## Plugin file structure

- `.github/workflows`: the [CI workflows](test_framework/ci.md) required to showcase your plugin's quality.
- `Makefile`: The entry point of the compilation of your plugin.
- `PLUGIN_SPECIFICATION.md`: The specification of the supported smart-contract and selectors of your plugin.
- `ethereum-plugin-sdk/`: This repository contains the interface between the Ethereum app and your plugin, as well as a lot of utility functions.
- `fuzzing/`: the [Fuzzer](test_framework/fuzzing.md) folder.
- `glyphs/`: The icon displayed by the Ethereum application when using the plugin on a Touchscreen device.
- `icons/`: The icons displayed on the device dashboard on any device.
- `ledger_app.toml`: the [Manifest](https://github.com/LedgerHQ/ledgered/blob/master/doc/manifest.md) of your plugin, used to bridge with the Ledger developed tools.
- `src/`: the source code of the plugin (in C).
- `tests/`: the [tests](test_framework/ragger.md) folder.
