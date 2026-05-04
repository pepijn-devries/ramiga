# The RamigaOutput R6 Class

A class to capture output from the Amiga emulator
([RamigaEmulator](https://pepijn-devries.github.io/ramiga/reference/RamigaEmulator.md)
class).

## Super class

[`ramiga::RamigaComponent`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.md)
-\> `RamigaOutput`

## Methods

### Public methods

- [`RamigaOutput$capture_frame()`](#method-RamigaOutput-capture_frame)

- [`RamigaOutput$capture_audio_buffer()`](#method-RamigaOutput-capture_audio_buffer)

- [`RamigaOutput$print()`](#method-RamigaOutput-print)

- [`RamigaOutput$clone()`](#method-RamigaOutput-clone)

Inherited methods

- [`ramiga::RamigaComponent$get_emulator()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_emulator)
- [`ramiga::RamigaComponent$get_pointer()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_pointer)
- [`ramiga::RamigaComponent$initialize()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-initialize)
- [`ramiga::RamigaComponent$list_options()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-list_options)

------------------------------------------------------------------------

### Method `capture_frame()`

Captures the current pixel information as sent to the monitor of the
virtual device.

#### Usage

    RamigaOutput$capture_frame(file, ...)

#### Arguments

- `file`:

  A path to a png file where to store the captured frame.

- `...`:

  Ignored

#### Returns

If file is missing it returns a `grDevice::as.raster()` object.
Otherwise, it will save it as png file to the specified path and returns
nothing.

------------------------------------------------------------------------

### Method `capture_audio_buffer()`

TODO

#### Usage

    RamigaOutput$capture_audio_buffer(file, ...)

#### Arguments

- `file`:

  TODO

- `...`:

  TODO

#### Returns

TODO

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
