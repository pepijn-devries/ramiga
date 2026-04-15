// #include <vector> //TODO
#include <filesystem>
#include "ramiga_types.h"

using namespace cpp11;
using namespace vamiga;

void vamiga_callback(const void* listener, Message msg) {
  // TODO printing messages from a separate thread is not safe
  // Better to collect messages and show at a safe moment.
  // Rprintf("TODO Emulator message: %u\n", msg);
}

void check_amiga(cpp11::external_pointer<VAmiga> amiga) {
  if (!amiga) cpp11::stop("Emulator no longer available");
}

[[cpp11::register]]
cpp11::external_pointer<VAmiga> create_amiga_() {
  VAmiga* vm = new VAmiga();
  // TODO call halt to end the currently launched thread.
  vm->launch(nullptr, vamiga_callback);
  return cpp11::external_pointer<VAmiga>(vm);
}

[[cpp11::register]]
SEXP start_amiga_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  if (!amiga->amiga.amiga->mem.hasRom()) {
    cpp11::package("utils")["flush.console"]();
    cpp11::warning("Emulator has not loaded a ROM.");
  }
  amiga->powerOn();
  return amiga;
}

[[cpp11::register]]
cpp11::integers get_framebuffer_vport_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  auto& vport = amiga->amiga.amiga->videoPort;
  
  isize x1, x2, y1, y2;
  vport.findInnerArea(x1, x2, y1, y2);
  
  int width = (int)(x2 - x1);
  int height = (int)(y2 - y1);
  
  const auto& texture = vport.getTexture();

  if (width <= 0 || height <= 0) {
    width = 320; // TODO
    height = 256; // TODO
  }
  
  cpp11::writable::integers result(width * height);

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int buf_idx = (y + (int)y1) * HPIXELS + (x + (int)x1);
      if (buf_idx > texture.pixels.size)
        cpp11::stop("No pixel information available");
      result[y + x * height] = (int)texture.pixels[buf_idx];
    }
  }
  
  result.attr("dim") = cpp11::integers({height, width});
  return result;
}

[[cpp11::register]]
double get_cpu_cycles_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  return (double)amiga->amiga.amiga->cpu.getCpuClock();
}

[[cpp11::register]]
cpp11::logicals emulator_info_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  auto& emuinfo = amiga->getInfo();
  writable::logicals result({
    emuinfo.powered, emuinfo.paused, emuinfo.running,
    emuinfo.suspended, emuinfo.warping, emuinfo.tracking
  });
  result.names() = {
    "powered", "paused", "running", "suspended", "warping", "tracking"};
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
uint32_t get_cpu_pc_(cpp11::external_pointer<vamiga::VAmiga> amiga) {
  check_amiga(amiga);
  return (uint32_t)amiga->amiga.amiga->cpu.getPC();
}

[[cpp11::register]]
void run_until_interrupted_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  amiga->run();
  cpp11::message("Emulator running, press <ESC> to pause");

  int count = 0;    
  while (true) {
    count++;
    if (count > 10000) {
      count = 0;
      amiga->amiga.amiga->audioPort.clear();
      
      try {
        cpp11::check_user_interrupt();
      } catch (...) {
        amiga->pause();
        // TODO this message is not shown consistently
        cpp11::package("utils")["flush.console"]();
        cpp11::message("Emulator is paused");
        return;
      }
    }
  }
}
