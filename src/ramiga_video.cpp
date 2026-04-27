#include <filesystem>
#include "ramiga_types.h"

[[cpp11::register]]
cpp11::integers get_framebuffer_vport_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  auto& vport = amiga->videoPort;
  
  isize x1 = 4 * HBLANK_CNT;
  isize x2 = 4 * PAL::HPOS_CNT;
  isize y1 = amiga->agnus.agnus->isPAL() ? PAL::VBLANK_CNT : NTSC::VBLANK_CNT;
  isize y2 = amiga->agnus.agnus->isPAL() ? PAL::VPOS_CNT_SF : NTSC::VPOS_CNT_SF;
  
  int width = (int)(x2 - x1);
  int height = (int)(y2 - y1);
  
  vport.lockTexture();
  const auto& texture = vport.getTexture();
  vport.unlockTexture();
  
  cpp11::writable::integers result(width * height);
  
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int buf_idx = (y + (int)y1) * HPIXELS + (x + (int)x1);
      // if (buf_idx > texture.size)
      //   cpp11::stop("No pixel information available"); TODO how to check size of texture?
      result[y + x * height] = (int)texture[buf_idx];
    }
  }
  
  result.attr("dim") = cpp11::integers({height, width});
  return result;
}


[[cpp11::register]]
void update_screen_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  auto* a = amiga->amiga.amiga;
  
  amiga->finishFrame();
  
  a->audioPort.clear();
  
  return;
}

[[cpp11::register]]
void update_scanline_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  auto* a = amiga->amiga.amiga;
  
  amiga->finishLine();
  
  a->audioPort.clear();
  
  return;
}
