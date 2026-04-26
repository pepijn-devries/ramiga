#include <filesystem>
#include "ramiga_types.h"

AudioPortAPI & get_audioport_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  return amiga->audioPort;
}