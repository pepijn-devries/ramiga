#include "ramiga_types.h"

[[cpp11::register]]
std::string rgb_to_hex(uint32_t val) {
  static constexpr char hex_digits[] = "0123456789ABCDEF";
  
  std::string res(7, '0');
  res[0] = '#';
  for (int i = 5; i >= 0; i--) {
    res[5 - i + (i%2)*2] = hex_digits[val & 0xf];
    val >>= 4;
  }
  return res;
}

[[cpp11::register]]
cpp11::strings get_framebuffer_vport_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  auto& vport = amiga->videoPort;
  vport.lockTexture();
  isize x1 = 4 * HBLANK_CNT;
  isize x2 = 4 * PAL::HPOS_CNT;
  isize y1 = amiga->agnus.agnus->isPAL() ? PAL::VBLANK_CNT : NTSC::VBLANK_CNT;
  isize y2 = amiga->agnus.agnus->isPAL() ? PAL::VPOS_CNT_SF : NTSC::VPOS_CNT_SF;
  
  int width = (int)(x2 - x1);
  int height = (int)(y2 - y1);
  const auto& texture = vport.getTexture();

  cpp11::writable::strings result(width * height);
  
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int buf_idx = (y + (int)y1) * HPIXELS + (x + (int)x1);
      result[y + x * height] = rgb_to_hex(texture[buf_idx]);
    }
  }
  vport.unlockTexture();
  
  result.attr("dim") = cpp11::integers({height, width});
  return result;
}


[[cpp11::register]]
void update_screen_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->finishFrame();
  while (!amiga->isPaused()) {
    std::this_thread::sleep_for(std::chrono::microseconds(21));
  }
  return;
}

[[cpp11::register]]
void update_scanline_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->finishLine();
  while (!amiga->isPaused()) {
    std::this_thread::sleep_for(std::chrono::microseconds(1)); 
  }
  return;
}

[[cpp11::register]]
void save_framebuffer_(cpp11::external_pointer<VAmigaWrapper> amiga,
                       std::string path) {
#ifdef USE_ZLIB
  check_amiga(amiga);
  auto& vport = amiga->videoPort;
  vport.lockTexture();
  save_png(path.c_str(), vport, amiga->agnus.agnus->isPAL());
  vport.unlockTexture();
#else
  cpp11::stop("Cannot save to PNG without zlib support");
#endif
}
