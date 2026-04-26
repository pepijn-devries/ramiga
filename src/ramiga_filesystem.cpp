#include <filesystem>
#include "ramiga_types.h"

using namespace retro::vault;

[[cpp11::register]]
void test_fs_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  retro::vault::Volume vol(*image);
  amiga::FileSystem fs = amiga::FileSystem(vol);
  Rprintf("TODO\n");
  return;
}

[[cpp11::register]]
cpp11::list fs_get_traits_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto vol = retro::vault::Volume(*image);
  auto fs = amiga::FileSystem(vol);
  
  const amiga::FSTraits & tr = fs.getTraits();
  return cpp11::writable::list({
    "dos"_nm = cpp11::writable::strings({ amiga::FSFormatEnum::_key(tr.dos) }),
      "block"_nm = cpp11::as_sexp((int)tr.blocks),
      "bytes"_nm = cpp11::as_sexp((int)tr.bytes),
      "bsize"_nm = cpp11::as_sexp((int)tr.bsize),
      "reserved"_nm = cpp11::as_sexp((int)tr.reserved),
      "type_ofs"_nm = cpp11::as_sexp(tr.ofs()),
      "type_ffs"_nm = cpp11::as_sexp(tr.ffs()),
      "type_intl"_nm = cpp11::as_sexp(tr.intl()),
      "type_adf"_nm = cpp11::as_sexp(tr.adf())
  });
}

[[cpp11::register]]
SEXP fs_describe_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto vol = retro::vault::Volume(*image);
  auto fs = amiga::FileSystem(vol);
  return cpp11::as_sexp(fs.describe());
}

[[cpp11::register]]
SEXP fs_is_formatted_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto vol = retro::vault::Volume(*image);
  auto fs = amiga::FileSystem(vol);
  return cpp11::as_sexp(fs.isFormatted());
}

[[cpp11::register]]
SEXP fs_get_name_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto vol = retro::vault::Volume(*image);
  auto fs = amiga::FileSystem(vol);
  BlockNr rb = fs.root();
  std::string volname = "";
  if (fs.isFormatted()) {
    const auto * rbl = fs.tryFetch(rb);
    amiga::FSName vn(rbl->data() + 432);
    volname = vn.c_str();
  }
  return cpp11::writable::strings({volname});
}

[[cpp11::register]]
uint32_t fs_num_allocated(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto vol = retro::vault::Volume(*image);
  auto fs = amiga::FileSystem(vol);
  uint32_t allocated = 0;
  if (fs.isFormatted()) {
    amiga::FSAllocator al(fs);
    allocated = al.numAllocated();
  }
  return allocated;
}