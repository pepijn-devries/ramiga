# The RamigaImage R6 Class

A virtual device represented by an image.

## Methods

### Public methods

- [`RamigaImage$new()`](#method-RamigaImage-new)

- [`RamigaImage$info()`](#method-RamigaImage-info)

- [`RamigaImage$size()`](#method-RamigaImage-size)

- [`RamigaImage$get_pointer()`](#method-RamigaImage-get_pointer)

- [`RamigaImage$is_formatted()`](#method-RamigaImage-is_formatted)

- [`RamigaImage$get_file_system()`](#method-RamigaImage-get_file_system)

- [`RamigaImage$print()`](#method-RamigaImage-print)

- [`RamigaImage$clone()`](#method-RamigaImage-clone)

------------------------------------------------------------------------

### Method `new()`

Initialise an image from a disk image file.

#### Usage

    RamigaImage$new(path)

#### Arguments

- `path`:

  File pointing to disk image file.

------------------------------------------------------------------------

### Method `info()`

Get information about the image.

#### Usage

    RamigaImage$info()

#### Returns

Returns a named `list` with information

------------------------------------------------------------------------

### Method `size()`

Get the size of the device represented by the image.

#### Usage

    RamigaImage$size()

#### Returns

Returns the size of the image in bytes.

------------------------------------------------------------------------

### Method `get_pointer()`

Get the pointer to the image object in memory

#### Usage

    RamigaImage$get_pointer(...)

#### Arguments

- `...`:

  Ignored.

#### Returns

Returns the `externalptr` pointing to the C++ class instance in memory.

------------------------------------------------------------------------

### Method `is_formatted()`

Determines if there is a file system present.

#### Usage

    RamigaImage$is_formatted()

#### Returns

Returns `logical` indicating if disk contains a file system.

------------------------------------------------------------------------

### Method `get_file_system()`

Get a file system from a virtual device if present

#### Usage

    RamigaImage$get_file_system(...)

#### Arguments

- `...`:

  Ignored.

#### Returns

Returns a
[RamigaFileSystem](https://pepijn-devries.github.io/ramiga/reference/RamigaFileSystem.md)
class object

------------------------------------------------------------------------

### Method [`print()`](https://rdrr.io/r/base/print.html)

Print some basic information about the device

#### Usage

    RamigaImage$print(...)

#### Arguments

- `...`:

  Ignored.

------------------------------------------------------------------------

### Method `clone()`

The objects of this class are cloneable with this method.

#### Usage

    RamigaImage$clone(deep = FALSE)

#### Arguments

- `deep`:

  Whether to make a deep clone.
