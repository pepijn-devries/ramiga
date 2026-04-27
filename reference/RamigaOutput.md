# The RamigaOutput R6 Class

A class to capture output from the Amiga emulator
([RamigaEmulator](https://pepijn-devries.github.io/ramiga/reference/RamigaEmulator.md)
class).

## Methods

### Public methods

- [`RamigaOutput$new()`](#method-RamigaOutput-new)

- [`RamigaOutput$print()`](#method-RamigaOutput-print)

- [`RamigaOutput$clone()`](#method-RamigaOutput-clone)

------------------------------------------------------------------------

### Method `new()`

Initialise a new Amiga emulator output object

#### Usage

    RamigaOutput$new(emulator)

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Prints basic information about the emulator output.

#### Usage

    RamigaOutput$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaOutput$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
