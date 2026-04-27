# The RamigaMemory R6 Class

The RamigaMemory class represents the memory of the emulated machine.
Use this object to interact with the machines memory.

## Methods

### Public methods

- [`RamigaMemory$new()`](#method-RamigaEmulator-new)

- [`RamigaMemory$load_rom()`](#method-RamigaEmulator-load_rom)

- [`RamigaMemory$has_rom()`](#method-RamigaEmulator-has_rom)

- [`RamigaMemory$get_rom_traits()`](#method-RamigaEmulator-get_rom_traits)

- [`RamigaMemory$get_config()`](#method-RamigaEmulator-get_config)

- [`RamigaMemory$print()`](#method-RamigaEmulator-print)

- [`RamigaMemory$clone()`](#method-RamigaEmulator-clone)

------------------------------------------------------------------------

### Method `new()`

The memory needs to be associated with an emulated machine. Therefore
you need the emulator to initiate a memory object.

#### Usage

    RamigaMemory$new(emulator)

#### Arguments

- `emulator`:

  An `RamigaEmulator` class object. The memory to be created needs to be
  associated with a virtual machine. The initiated object will represent
  the memory of the emulated machine.

------------------------------------------------------------------------

### Method `load_rom()`

Load an operating system to ROM. It can be an official Kickstart ROM
image, or the rom provided for AROS Research Operating System.

#### Usage

    RamigaMemory$load_rom(path)

#### Arguments

- `path`:

  File path pointing to the location of the ROM file.

#### Returns

Returns the updated RamigaMemory object.

------------------------------------------------------------------------

### Method `has_rom()`

Check if a ROM image was successfully loaded

#### Usage

    RamigaMemory$has_rom()

#### Returns

Returns a `logical` value.

------------------------------------------------------------------------

### Method `get_rom_traits()`

Get ROM characteristics if known.

#### Usage

    RamigaMemory$get_rom_traits()

#### Returns

Returns `NULL` if no ROM has been loaded. It will return A named list
with ROM traits otherwise.

------------------------------------------------------------------------

### Method `get_config()`

Get details on the configuration of the emulated memory

#### Usage

    RamigaMemory$get_config()

#### Returns

Returns a named `list` with memory configurations.

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Print some basic information about the emulated memory.

#### Usage

    RamigaMemory$print(...)

#### Arguments

- `...`:

  Ignored.

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaMemory$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
