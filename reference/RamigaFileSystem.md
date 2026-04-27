# The RamigaFileSystem R6 Class

Obtain the file system from a virtual device (if available), such that
you can interact with it.

## Methods

### Public methods

- [`RamigaFileSystem$new()`](#method-RamigaFileSystem-new)

- [`RamigaFileSystem$get_volume_name()`](#method-RamigaFileSystem-get_volume_name)

- [`RamigaFileSystem$get_traits()`](#method-RamigaFileSystem-get_traits)

- [`RamigaFileSystem$print()`](#method-RamigaFileSystem-print)

- [`RamigaFileSystem$clone()`](#method-RamigaFileSystem-clone)

------------------------------------------------------------------------

### Method `new()`

Attempt to access the file system on a device image if available

#### Usage

    RamigaFileSystem$new(image)

#### Arguments

- `image`:

  The virtual device (represented by a
  [RamigaImage](https://pepijn-devries.github.io/ramiga/reference/RamigaImage.md)
  class object), from which the file system should be retrieved

------------------------------------------------------------------------

### Method `get_volume_name()`

Get the name of the volume of that contains the file system

#### Usage

    RamigaFileSystem$get_volume_name()

#### Returns

Returns the name of the volume

------------------------------------------------------------------------

### Method `get_traits()`

Get some traits of the file system.

#### Usage

    RamigaFileSystem$get_traits(...)

#### Arguments

- `...`:

  Ignored

#### Returns

Returns a named `list` of file system traits.

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Prints basic info about the file system

#### Usage

    RamigaFileSystem$print(...)

#### Arguments

- `...`:

  Ignored.

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaFileSystem$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
