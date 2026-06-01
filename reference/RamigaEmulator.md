# The RamigaEmulator R6 Class

A class representing the emulator for emulating an Amiga.

## Super class

[`ramiga::RamigaComponent`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.md)
-\> `RamigaEmulator`

## Active bindings

- `memory`:

  The emulated memory, represented by
  [RamigaMemory](https://pepijn-devries.github.io/ramiga/reference/RamigaMemory.md)

- `cpu`:

  The emulated CPU, represented by
  [RamigaCPU](https://pepijn-devries.github.io/ramiga/reference/RamigaCPU.md)

- `floppy_drives`:

  The emulated floppy drives, represented by a named `list` of
  [RamigaFloppyDrive](https://pepijn-devries.github.io/ramiga/reference/RamigaFloppyDrive.md)
  objects.

- `control_ports`:

  Control ports to which a virtual mouse or joystick can be connected.
  It is represented by the
  [RamigaControlPort](https://pepijn-devries.github.io/ramiga/reference/RamigaControlPort.md)
  class.

- `output`:

  Get object to capture emulator output. Handled by
  [RamigaOutput](https://pepijn-devries.github.io/ramiga/reference/RamigaOutput.md).

## Methods

### Public methods

- [`RamigaEmulator$new()`](#method-RamigaEmulator-new)

- [`RamigaEmulator$power_on()`](#method-RamigaEmulator-power_on)

- [`RamigaEmulator$power_off()`](#method-RamigaEmulator-power_off)

- [`RamigaEmulator$soft_reset()`](#method-RamigaEmulator-soft_reset)

- [`RamigaEmulator$hard_reset()`](#method-RamigaEmulator-hard_reset)

- [`RamigaEmulator$run()`](#method-RamigaEmulator-run)

- [`RamigaEmulator$next_frame()`](#method-RamigaEmulator-next_frame)

- [`RamigaEmulator$fast_forward()`](#method-RamigaEmulator-fast_forward)

- [`RamigaEmulator$get_info()`](#method-RamigaEmulator-get_info)

- [`RamigaEmulator$get_config()`](#method-RamigaEmulator-get_config)

- [`RamigaEmulator$set_config()`](#method-RamigaEmulator-set_config)

- [`RamigaEmulator$get_version()`](#method-RamigaEmulator-get_version)

- [`RamigaEmulator$print()`](#method-RamigaEmulator-print)

- [`RamigaEmulator$clone()`](#method-RamigaEmulator-clone)

Inherited methods

- [`ramiga::RamigaComponent$get_emulator()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_emulator)
- [`ramiga::RamigaComponent$get_pointer()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_pointer)
- [`ramiga::RamigaComponent$list_options()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-list_options)

------------------------------------------------------------------------

### Method `new()`

Initialise a new Amiga emulator

#### Usage

    RamigaEmulator$new()

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

### Method `hard_reset()`

A hard reset. Same as powering of the machine, then powering it back on.

#### Usage

    RamigaEmulator$hard_reset()

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

### Method `next_frame()`

Update the machines state to the next video frame. The machine runs
until the vertical blank is reached and pauses immediately.

#### Usage

    RamigaEmulator$next_frame()

#### Returns

Returns the emulator object

------------------------------------------------------------------------

### Method `fast_forward()`

Runs the emulator at warp speed and skips the specified number of frames

#### Usage

    RamigaEmulator$fast_forward(frames)

#### Returns

Returns the emulator object

------------------------------------------------------------------------

### Method `get_info()`

Get information about the emulator state.

#### Usage

    RamigaEmulator$get_info()

#### Returns

Returns a named list.

------------------------------------------------------------------------

### Method `get_config()`

Get information about the emulator configuration.

#### Usage

    RamigaEmulator$get_config()

#### Returns

Returns a named list.

------------------------------------------------------------------------

### Method `set_config()`

Quickly set the emulator configuration to one of the pre-specified
schemes.

#### Usage

    RamigaEmulator$set_config(scheme = "A500_OCS_1MB", ...)

#### Arguments

- `scheme`:

  Should be one of the following strings: `"A1000_OCS_1MB"`,
  `"A500_OCS_1MB"` (default), `"A500_ECS_1MB"`, or `"A500_PLUS_1MB"`.

- `...`:

  Ignored

#### Returns

Returns a string

------------------------------------------------------------------------

### Method `get_version()`

Get the version number of the vAmiga core used by this package

#### Usage

    RamigaEmulator$get_version(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns a string

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Prints basic information about the emulator.

#### Usage

    RamigaEmulator$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaEmulator$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
