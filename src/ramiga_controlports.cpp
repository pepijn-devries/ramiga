#include "ramiga_types.h"

ControlPort& get_control_port_(cpp11::external_pointer<VAmiga> amiga,
                               int port_number) {
  check_amiga(amiga);
  if (port_number < 1 || port_number > 2)
    cpp11::stop("Invalid port number");
  auto& port = port_number == 1 ? amiga->controlPort1.controlPort :
    amiga->controlPort2.controlPort;
  return *port;
}

[[cpp11::register]]
cpp11::external_pointer<Joystick> joystick_(cpp11::external_pointer<VAmiga> amiga,
                                            int port_number) {
  auto & port = get_control_port_(amiga, port_number);
  Joystick * joy = new Joystick(*amiga->amiga.amiga, port);
  return cpp11::external_pointer<Joystick>(joy);
}

[[cpp11::register]]
cpp11::external_pointer<Mouse> mouse_(cpp11::external_pointer<VAmiga> amiga,
                                            int port_number) {
  auto & port = get_control_port_(amiga, port_number);
  Mouse * m = new Mouse(*amiga->amiga.amiga, port);
  return cpp11::external_pointer<Mouse>(m);
}