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
SEXP poweron_amiga_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  amiga->powerOn();
  return amiga;
}

[[cpp11::register]]
SEXP poweroff_amiga_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  amiga->powerOff();
  return amiga;
}

[[cpp11::register]]
SEXP softreset_amiga_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  amiga->softReset();
  return amiga;
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
void run_until_interrupted_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  amiga->run();
  cpp11::message("Emulator running, press <ESC> to pause");

  int count = 0;    
  while (true) {
    count++;
    if (count > 10000) {
      count = 0;
      amiga->audioPort.port->clear();
      
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
