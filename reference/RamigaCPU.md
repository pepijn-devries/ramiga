# The RamigaCPU R6 Class

A class that represents the emulator's Central Processing Unit (CPU).

## Methods

### Public methods

- [`RamigaCPU$new()`](#method-RamigaCPU-new)

- [`RamigaCPU$get_cycles()`](#method-RamigaCPU-get_cycles)

- [`RamigaCPU$get_program_counter()`](#method-RamigaCPU-get_program_counter)

- [`RamigaCPU$get_config()`](#method-RamigaCPU-get_config)

- [`RamigaCPU$print()`](#method-RamigaCPU-print)

- [`RamigaCPU$clone()`](#method-RamigaCPU-clone)

------------------------------------------------------------------------

### Method `new()`

Initialise a RamigaCPU class object.

#### Usage

    RamigaCPU$new(emulator)

#### Arguments

- `emulator`:

  An `RamigaEmulator` class object. The CPU to be created needs to be
  associated with a virtual machine. The initiated object will represent
  the CPU of the emulated machine.

------------------------------------------------------------------------

### Method `get_cycles()`

Get the CPU cycle count since the emulator started

#### Usage

    RamigaCPU$get_cycles()

#### Returns

Returns the count in number of cycles

------------------------------------------------------------------------

### Method `get_program_counter()`

Get the memory address of the currently running program

#### Usage

    RamigaCPU$get_program_counter()

#### Returns

On the Amiga memory addresses are mapped as 32 bit unsigned integers. As
R doesn't support this type, it is returned as a `numeric` (double)
value.

------------------------------------------------------------------------

### Method `get_config()`

Get current CPU configuration details

#### Usage

    RamigaCPU$get_config()

#### Returns

Returns a named list

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Print some basic information about the CPU

#### Usage

    RamigaCPU$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaCPU$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
