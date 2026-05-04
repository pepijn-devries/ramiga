# ramiga

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
#> Amiga emulator (PAL) powered on:
#>   CPU: 68000
#>   Memory: chip 0.5Mb; slow 0.5Mb; fast 0.0Mb; ROM: Not loaded
```

## Not on CRAN

This package will not be appearing on CRAN any time soon. If this
package were to be submitted to CRAN there are several hurdles to be
taken:

- All code should comply with ISO standards.
  - With some effort this would be achievable
- Package size should not exceed 5 MB, but should at best be below 10 MB
  - This will be difficult, if we want to keep all features
- We should avoid using non-standard compilation flags (like
  -Wa,-mbig-obj)
  - This could be fixed by splitting up large objects into multiple
    smaller ones.
- This package relies heavily on C++20 features. This will not fly on
  all CRAN build and check machines (which is a requirement).
  - This will take way too much effort to convert to CRAN acceptable
    alternatives.

I pay as much attention to quality as any of my other R packages, so you
should be able to enjoy using this package. But for the reasons stated
above, I will not submit to CRAN. You can install it from R-Universe as
specified above.

*Why not use libretro?* I did explore this avenue. It doesn’t need
C++20, so in that respect it would be easier to get on CRAN. However,
the library is much bulkier than vAmiga. It also doesn’t have a sleek
and easy to implement API like vAmiga. So I’ll leave this challenge for
someone else to confront.
