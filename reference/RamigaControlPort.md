# The RamigaControlPort R6 Class

A class that represents the emulator's control ports (for mouse and
joystick).

## Super class

[`ramiga::RamigaComponent`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.md)
-\> `RamigaControlPort`

## Active bindings

- `device`:

  This field tells you which device (mouse, joystick or none) is
  connected to the current port. Should be a
  [RamigaControlDevice](https://pepijn-devries.github.io/ramiga/reference/RamigaControlDevice.md)
  class object, or `NULL` if there is no device.

## Methods

### Public methods

- [`RamigaControlPort$new()`](#method-RamigaControlPort-new)

- [`RamigaControlPort$print()`](#method-RamigaControlPort-print)

- [`RamigaControlPort$clone()`](#method-RamigaControlPort-clone)

Inherited methods

- [`ramiga::RamigaComponent$get_emulator()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_emulator)
- [`ramiga::RamigaComponent$get_pointer()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_pointer)
- [`ramiga::RamigaComponent$list_options()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-list_options)

------------------------------------------------------------------------

### Method `new()`

#### Usage

    RamigaControlPort$new(emulator, port_number = 1L, device = NULL)

#### Arguments

- `emulator`:

  An `RamigaEmulator` class object. The control port to be created needs
  to be associated with a virtual machine. The initiated object will
  represent the control port of the emulated machine.

- `port_number`:

  The Amiga has two control ports. This number specifies which one we
  are using. Should be either 1 or 2.

- `device`:

  Device connected to this port. An
  [RamigaControlDevice](https://pepijn-devries.github.io/ramiga/reference/RamigaControlDevice.md)
  class object or `NULL` if there is no device.

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Print some basic information about the control port.

#### Usage

    RamigaControlPort$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaControlPort$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
