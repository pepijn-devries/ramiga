# The RamigaEmulator R6 Class

A class representing the emulator for emulating an Amiga.

## Methods

### Public methods

- [`RamigaEmulator$new()`](#method-RamigaEmulator-new)

- [`RamigaEmulator$get_memory()`](#method-RamigaEmulator-get_memory)

- [`RamigaEmulator$get_cpu()`](#method-RamigaEmulator-get_cpu)

- [`RamigaEmulator$get_floppy_drive()`](#method-RamigaEmulator-get_floppy_drive)

- [`RamigaEmulator$power_on()`](#method-RamigaEmulator-power_on)

- [`RamigaEmulator$power_off()`](#method-RamigaEmulator-power_off)

- [`RamigaEmulator$soft_reset()`](#method-RamigaEmulator-soft_reset)

- [`RamigaEmulator$run()`](#method-RamigaEmulator-run)

- [`RamigaEmulator$get_info()`](#method-RamigaEmulator-get_info)

- [`RamigaEmulator$get_pointer()`](#method-RamigaEmulator-get_pointer)

- [`RamigaEmulator$get_output()`](#method-RamigaEmulator-get_output)

- [`RamigaEmulator$print()`](#method-RamigaEmulator-print)

- [`RamigaEmulator$clone()`](#method-RamigaEmulator-clone)

------------------------------------------------------------------------

### Method `new()`

Initialise a new Amiga emulator

#### Usage

    RamigaEmulator$new()

------------------------------------------------------------------------

### Method `get_memory()`

Get a representation of the machine's emulated memory

#### Usage

    RamigaEmulator$get_memory()

#### Returns

Returns a
[RamigaMemory](https://pepijn-devries.github.io/ramiga/reference/RamigaMemory.md)
class object

------------------------------------------------------------------------

### Method `get_cpu()`

Get a representation of the machine's Central Processing Unit

#### Usage

    RamigaEmulator$get_cpu()

#### Returns

Returns a
[RamigaCPU](https://pepijn-devries.github.io/ramiga/reference/RamigaCPU.md)
class object.

------------------------------------------------------------------------

### Method `get_floppy_drive()`

Get a specific floppy drive from the emulated machine

#### Usage

    RamigaEmulator$get_floppy_drive(drive_number)

#### Arguments

- `drive_number`:

  The emulator has 4 floppy drives, numbered 0 to 3. Pick which drive
  you want to operate

#### Returns

Returns a
[RamigaFloppyDrive](https://pepijn-devries.github.io/ramiga/reference/RamigaFloppyDrive.md)
class object.

------------------------------------------------------------------------

### Method `power_on()`

When the emulator is initialised it is powered off. Call this to power
on the virtual machine.

#### Usage

    RamigaEmulator$power_on()

#### Returns

Returns the emulator object

------------------------------------------------------------------------

### Method `power_off()`

Power off emulator. Advisable if you plan to make adjustments to the
emulated hardware configuration.

#### Usage

    RamigaEmulator$power_off()

#### Returns

Returns the emulator object

------------------------------------------------------------------------

### Method `soft_reset()`

A soft reset, just resets the CPU, causing the system to reboot. This is
similar to simultaneously pressing and both keys on an original machine.

#### Usage

    RamigaEmulator$soft_reset()

#### Returns

Returns the emulator object

------------------------------------------------------------------------

### Method `run()`

When initialised, the emulator is paused. Call this to start running the
virtual machine. It will hold up the R thread untill you interrupt (by
pressing ). After the interrupt the machine will be paused.

#### Usage

    RamigaEmulator$run()

#### Returns

Returns NULL invisibly.

------------------------------------------------------------------------

### Method `get_info()`

Get information about the emulator state.

#### Usage

    RamigaEmulator$get_info()

#### Returns

Returns a named list.

------------------------------------------------------------------------

### Method `get_pointer()`

Get the pointer to the emulator object in memory

#### Usage

    RamigaEmulator$get_pointer(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns the `externalptr` pointing to the C++ class instance in memory

------------------------------------------------------------------------

### Method `get_output()`

Get object to capture emulator output.

#### Usage

    RamigaEmulator$get_output(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns
[RamigaOutput](https://pepijn-devries.github.io/ramiga/reference/RamigaOutput.md)
class object

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

#### Usage

    RamigaEmulator$print(...)

#### Arguments

- `...`:

  Ignored Prints basic information about the emulator.

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaEmulator$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
