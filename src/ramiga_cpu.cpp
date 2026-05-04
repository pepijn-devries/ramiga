#include <filesystem>
#include "ramiga_types.h"

CPUAPI & get_cpu_(cpp11::external_pointer<VAmiga> amiga) {
  check_amiga(amiga);
  return amiga->cpu;
}

[[cpp11::register]]
double get_cpu_cycles_(cpp11::external_pointer<VAmiga> amiga) {
  return get_cpu_(amiga).cpu->getCpuClock();
}

[[cpp11::register]]
uint32_t get_cpu_pc_(cpp11::external_pointer<vamiga::VAmiga> amiga) {
  return get_cpu_(amiga).cpu->getPC();
}

[[cpp11::register]]
cpp11::list get_cpu_config_(cpp11::external_pointer<vamiga::VAmiga> amiga) {
  const CPUConfig conf = get_cpu_(amiga).getConfig();
  return cpp11::writable::list({
    "revision"_nm =
      cpp11::writable::strings({ CPURevEnum::_key(conf.revision) }),
      "register_reset_value"_nm =
        cpp11::writable::doubles({ (double)conf.regResetVal }),
        "overclocking"_nm =
          cpp11::writable::doubles({ (double)conf.overclocking })
  });
}
