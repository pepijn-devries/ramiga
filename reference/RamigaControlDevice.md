# The RamigaControlDevice R6 Class

A class that represents control devices, like the mouse or joystick.

## Super class

[`ramiga::RamigaComponent`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.md)
-\> `RamigaControlDevice`

## Methods

### Public methods

- [`RamigaControlDevice$new()`](#method-RamigaControlDevice-new)

- [`RamigaControlDevice$print()`](#method-RamigaControlDevice-print)

- [`RamigaControlDevice$clone()`](#method-RamigaControlDevice-clone)

Inherited methods

- [`ramiga::RamigaComponent$get_emulator()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_emulator)
- [`ramiga::RamigaComponent$get_pointer()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_pointer)
- [`ramiga::RamigaComponent$list_options()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-list_options)

------------------------------------------------------------------------

### Method `new()`

#### Usage

    RamigaControlDevice$new(emulator, port_number, type)

#### Arguments

- `emulator`:

  A virtual control device only is meaningful when connected to a
  virtual device. Therefore, you need an emulator
  ([RamigaEmulator](https://pepijn-devries.github.io/ramiga/reference/RamigaEmulator.md))
  to connect the device to.

- `port_number`:

  Port on the virtual machine to which the device is connected. Should
  be either port 1 or 2.

- `type`:

  Type of device, should be either `"mouse"`, or `"joystick"`.

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Prints some basic information about the control device

#### Usage

    RamigaControlDevice$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaControlDevice$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
