
# ramiga <a href="https://pepijn-devries.github.io/ramiga/"><img src="man/figures/logo.svg" align="right" height="139" alt="ramiga website" /></a>

<!-- badges: start -->

[![R-CMD-check](https://github.com/pepijn-devries/ramiga/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/pepijn-devries/ramiga/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The status of this package is currently highly experimental. It provides
R bindings to the [vAmiga](https://github.com/dirkwhoffmann/vamiga)
emulator.

It will:

- Provide programmatic access to the emulator
- Emulate Amiga’s with the original chip set.
  - So, neither enhanced chip set nor the Advanced Graphics Architecture
    are supported
- Capture output
- Provide input (mouse movements, keyboard events, etc.)
  programmatically

It will **not**:

- Provide full interactive visuals and peripherals
  - There is simply no way to exchange this information between the R
    environment and the emulator with sufficient speed and efficiency.

## Installation

You can install the development version of ramiga like so:

``` r
remotes::install_github("pepijn-devries/ramiga")
```

## Example

``` r
library(ramiga)
emu <- RamigaEmulator$new()

emu$power_on()
#> TODO
```

## Things to do

- Extensive checking for CRAN compliance
  - Make sure that all structs are named (either upstream or in this
    fork). CRAN allows only ISO compliant code. Anonymous structs are
    not ISO.
  - Remove any redundant/unused code. The size of the package will
    trigger a warning as is. So, try to keep it as small as possible.
  - Add CRAN comments to justify non-compliance to CRAN policies (e.g.,
    -Wa,-mbig-obj flags required on Windows). Or split Moira.cpp (the
    suspected issue) into multiple smaller pieces of code
- Add zlib-support to platforms other than Windows
- Implement features
- Add decent documentation
