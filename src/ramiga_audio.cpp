#include <filesystem>
#include "ramiga_types.h"

AudioPortAPI & get_audioport_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  return amiga->audioPort;
}

[[cpp11::register]]
cpp11::doubles mono_audio_buffer_(cpp11::external_pointer<VAmiga> amiga) {
  auto & port = get_audioport_(amiga);
  isize buf_size = port.getConfig().bufferSize;
  std::vector<float> buff(buf_size, 0.0f);
  isize nread = port.copyMono(buff.data(), buf_size);
  cpp11::writable::doubles result((R_xlen_t)nread);
  for (isize i = 0; i < nread; i++) {
    result[(R_xlen_t)i] = buff[i];
  }
  return result;
}

//TODO
// isize copyStereo(float *left, float *right, isize n);
