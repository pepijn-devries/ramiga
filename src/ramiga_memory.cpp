#include "ramiga_types.h"

[[cpp11::register]]
SEXP load_rom_(cpp11::external_pointer<VAmiga> amiga, std::string path) {
  check_amiga(amiga);
  std::filesystem::path p(path);
  amiga->mem.loadRom(p);
  return amiga;
}

[[cpp11::register]]
SEXP load_rom_ext_(cpp11::external_pointer<VAmiga> amiga, std::string path) {
  check_amiga(amiga);
  std::filesystem::path p(path);
  amiga->mem.loadExt(p);
  return amiga;
}

[[cpp11::register]]
bool has_rom_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  return amiga->mem.mem->hasRom();
}
