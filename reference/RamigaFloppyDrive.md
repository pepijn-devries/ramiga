# The RamigaFlopyDrive R6 Class

A class that represents the emulator's floppy drive.

## Super class

[`ramiga::RamigaComponent`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.md)
-\> `RamigaFloppyDrive`

## Methods

### Public methods

- [`RamigaFloppyDrive$new()`](#method-RamigaFloppyDrive-new)

- [`RamigaFloppyDrive$insert_disk()`](#method-RamigaFloppyDrive-insert_disk)

- [`RamigaFloppyDrive$eject_disk()`](#method-RamigaFloppyDrive-eject_disk)

- [`RamigaFloppyDrive$get_info()`](#method-RamigaFloppyDrive-get_info)

- [`RamigaFloppyDrive$print()`](#method-RamigaFloppyDrive-print)

- [`RamigaFloppyDrive$clone()`](#method-RamigaFloppyDrive-clone)

Inherited methods

- [`ramiga::RamigaComponent$get_emulator()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_emulator)
- [`ramiga::RamigaComponent$get_pointer()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-get_pointer)
- [`ramiga::RamigaComponent$list_options()`](https://pepijn-devries.github.io/ramiga/reference/RamigaComponent.html#method-list_options)

------------------------------------------------------------------------

### Method `new()`

#### Usage

    RamigaFloppyDrive$new(emulator, drive_number = 0)

#### Arguments

- `emulator`:

  An `RamigaEmulator` class object. The floppy drive to be created needs
  to be associated with a virtual machine. The initiated object will
  represent the floppy drive of the emulated machine.

- `drive_number`:

  The emulator has 4 floppy drives, numbered 0 to 3. Pick which drive
  you want to operate

------------------------------------------------------------------------

### Method `insert_disk()`

Insert a virtual floppy disk in the virtual floppy drive.

#### Usage

    RamigaFloppyDrive$insert_disk(disk, write_protected = TRUE)

#### Arguments

- `disk`:

  A floppy disk represented by a
  [RamigaImage](https://pepijn-devries.github.io/ramiga/reference/RamigaImage.md)
  class object.

- `write_protected`:

  `logical` value indicating whether the inserted disk needs to be write
  protected. Default is `TRUE`

------------------------------------------------------------------------

### Method `eject_disk()`

Eject a virtual floppy disk from the virtual drive

#### Usage

    RamigaFloppyDrive$eject_disk(delay = 0)

#### Arguments

- `delay`:

  Delay for ejecting the disk counted in CPU cycles.

------------------------------------------------------------------------

### Method `get_info()`

Get information about the floppy drive

#### Usage

    RamigaFloppyDrive$get_info()

#### Returns

Returns a named list with information

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Prints some basic information about the floppy drive

#### Usage

    RamigaFloppyDrive$print(...)

#### Arguments

- `...`:

  Ignored

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaFloppyDrive$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
