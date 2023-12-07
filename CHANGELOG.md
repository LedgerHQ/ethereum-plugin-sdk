# Ethereum Plugin SDK changelog

|          Icon        |            Impact             |
|----------------------|-------------------------------|
| :rotating_light:     | Breaks build                  |
| :warning:            | Breaks compatibility with app |

## [latest](/) - 2023/12/07

### Fixed

* standard\_plugin build ([this PR on the SDK](https://github.com/LedgerHQ/ledger-secure-sdk/pull/473) had broken it)
* Broken variant auto-setting in the standard\_plugin Makefile
* Missing null-check on parameters received by the plugins

### Changed

* utils renamed to plugin\_utils to prevent filename conflicts in plugins

## [4d8e044](/../../commit/4d8e044) - 2023/11/09

### Added

* standard\_plugin Makefile so plugins can use it & have a really small Makefile
with only the relevant information
* Comments in the plugin interface header file

## [1fe4085](/../../commit/1fe4085) - 2023/10/19

### Changed

* Now only uses *\_no\_throw* functions, SDK functions now return a boolean
(keeps the guidelines enforcer happy)

### Added

* *main* & *dispatch\_call* functions are now part of the SDK and don't need to
be implemented by each plugin :rotating_light:

## [b9777e7](/../../commit/b9777e7) - 2023/05/16

### Added

* Stax support with information passed from plugin to app-ethereum (with caller app struct)

## [a4b971f](/../../commit/a4b971f) - 2023/01/24

### Changed

* Removed end space in tickers :warning:

## [81eb658](/../../commit/81eb658) - 2022/11/17

### Added

* *U2BE\_from\_parameter* & *U4BE\_from\_parameter* safe functions
