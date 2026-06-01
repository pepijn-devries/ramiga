#include <filesystem>
#include <vector>
#include "ramiga_types.h"

using namespace cpp11;
using namespace vamiga;

void vamiga_callback(const void* listener, Message msg) {
  // TODO printing messages from a separate thread is not safe
  // Better to collect messages and show at a safe moment.
  // Rprintf("TODO Emulator message: %u\n", msg);
}

void check_amiga(cpp11::external_pointer<VAmigaWrapper> amiga) {
  if (!amiga) cpp11::stop("Emulator no longer available");
}

[[cpp11::register]]
cpp11::external_pointer<VAmigaWrapper> create_amiga_() {
  VAmigaWrapper* vm = new VAmigaWrapper();
  // TODO call halt to end the currently launched thread.
  vm->launch(nullptr, vamiga_callback);
  return cpp11::external_pointer<VAmigaWrapper>(vm);
}

[[cpp11::register]]
SEXP poweron_amiga_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->powerOn();
  return amiga;
}

[[cpp11::register]]
SEXP poweroff_amiga_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->powerOff();
  return amiga;
}

[[cpp11::register]]
SEXP softreset_amiga_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->softReset();
  return amiga;
}

[[cpp11::register]]
SEXP hardreset_amiga_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  amiga->hardReset();
  return amiga;
}

[[cpp11::register]]
cpp11::logicals emulator_info_(cpp11::external_pointer<VAmigaWrapper> amiga) {
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
cpp11::list emulator_config_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  auto & conf = amiga->amiga.getConfig();
  return writable::list({
    "tv"_nm = writable::strings({TVEnum::_key(conf.type)}),
    "warp_boot"_nm = cpp11::as_sexp((double)conf.warpBoot),
    "warp_mode"_nm = writable::strings({WarpEnum::_key(conf.warpMode)}),
    "speed_boost"_nm = cpp11::as_sexp((double)conf.speedBoost),
    "vsync"_nm = cpp11::as_sexp(conf.vsync),
    "run_ahead"_nm = cpp11::as_sexp((double)conf.runAhead),
    "auto_snapshots"_nm = cpp11::as_sexp(conf.autoSnapshots),
    "snapshot_compressor"_nm = 
      cpp11::writable::strings({CompressorEnum::_key(conf.snapshotCompressor)}),
    "compress_workspaces"_nm =
      cpp11::as_sexp(conf.compressWorkspaces)
  });
}

[[cpp11::register]]
void run_until_interrupted_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  amiga->run();
  cpp11::message("Emulator running, press <ESC> to pause");

  int count = 0;    
  while (true) {
    count++;
    if (count > 10000) {
      count = 0;

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

[[cpp11::register]]
cpp11::strings emulator_version_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  return writable::strings({amiga->version()});
}

[[cpp11::register]]
void emu_set_config_scheme_(cpp11::external_pointer<VAmigaWrapper> amiga,
                                     std::string config_scheme) {
  check_amiga(amiga);
  bool success = false;
  for (long i = ConfigSchemeEnum::minVal; i <= ConfigSchemeEnum::maxVal; ++i) {
    ConfigScheme val = static_cast<ConfigScheme>(i);
    if (config_scheme == ConfigSchemeEnum::_key(val)) {
      amiga->set(val);
      success = true;
      break;
    }
  }
  if (!success) cpp11::stop("Failed to set emulator scheme");
  return;
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
void ffw_(cpp11::external_pointer<VAmigaWrapper> amiga, int frames) {
  if (frames <= 0)
    cpp11::stop("Can only fast forward positive number of frames");
  check_amiga(amiga);
  amiga->amiga.amiga->fastForward(frames);
  while (!amiga->isPaused()) {
    std::this_thread::sleep_for(std::chrono::microseconds(21));
  }
  return;
}
