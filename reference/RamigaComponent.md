# The RamigaComponent R6 Class

An abstract class to represent emulator components. Each of the emulator
components inherit from this class. It provides consistent access to and
control over component specific options.

## Active bindings

- `options`:

  A named `list` of options. You can get and set all individual
  elements. Elements are always returned as `character`, but can be also
  be set as `numeric` or `logical`, depending on the specific option.
  Assignment values are always parsed by the vAmiga engine.

## Methods

### Public methods

- [`RamigaComponent$new()`](#method-RamigaComponent-new)

- [`RamigaComponent$get_pointer()`](#method-RamigaComponent-get_pointer)

- [`RamigaComponent$get_emulator()`](#method-RamigaComponent-get_emulator)

- [`RamigaComponent$list_options()`](#method-RamigaComponent-list_options)

- [`RamigaComponent$clone()`](#method-RamigaComponent-clone)

------------------------------------------------------------------------

### Method `new()`

Most emulator components don't need to be initialised. It's simplest to
create an emulator with `RamigaEmulator$new()`. All components can be
accessed through the R6 object fields.

#### Usage

    RamigaComponent$new(emulator, ...)

#### Arguments

- `emulator`:

  All emulator components should be part of an emulator. All components
  (except for the emulator itself) therefore needs the, initialised with
  an emulator.

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `get_pointer()`

Get the pointer to the emulator object in memory

#### Usage

    RamigaComponent$get_pointer(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns the `externalptr` pointing to the C++ class instance in memory

------------------------------------------------------------------------

### Method `get_emulator()`

Get associated emulator.

#### Usage

    RamigaComponent$get_emulator(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns a
[RamigaEmulator](https://pepijn-devries.github.io/ramiga/reference/RamigaEmulator.md)
class object instance in memory

------------------------------------------------------------------------

### Method `list_options()`

List available options for the emulator component. It shows the name of
the option and indicates their intended value(s).

#### Usage

    RamigaComponent$list_options(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns a named `list` with available options.

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaComponent$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
