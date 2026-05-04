#include "ramiga_types.h"

Configurable& configurable_from_id(int component_id,
                                   cpp11::external_pointer<VAmiga> amiga,
                                   int index) {
  check_amiga(amiga);
  switch(component_id) {
  case RAMIGA_COMP_EMULATOR:
    return *amiga->amiga.amiga;
    break;
  case RAMIGA_COMP_CPU:
    return *amiga->cpu.cpu;
    break;
  case RAMIGA_COMP_MEMORY:
    return *amiga->mem.mem;
    break;
  case RAMIGA_COMP_FLOPPYDRIVE:
    return *amiga->df[index]->drive;
    break;
  case RAMIGA_COMP_CONTROLPORT:
    return index == 1 ? *amiga->controlPort1.controlPort :
      *amiga->controlPort2.controlPort;
    break;
  case RAMIGA_COMP_VIDEO:
    return *amiga->videoPort.videoPort;
    break;
  case RAMIGA_COMP_AUDIO:
    return *amiga->audioPort.port;
    break;
  default:
    cpp11::stop("Undefined component ID");
  }
}

cpp11::list list_options_(Configurable & conf) {
  const auto & opts = conf.getOptions();
  cpp11::writable::list result((R_xlen_t)opts.size());
  cpp11::writable::strings nms((R_xlen_t)opts.size());
  R_xlen_t i = 0;
  for (const auto& opt : opts) {
    result[i] = cpp11::as_sexp(OptionParser::argList(opt));
    nms[i] = OptEnum::_key(opt);
    i++;
  }
  result.attr("names") = nms;
  return result;
}

cpp11::sexp get_option_(Configurable & conf, const std::string & key) {
  const auto & opts = conf.getOptions();
  for (const auto& opt : opts) {
    if (key == OptEnum::_key(opt)) {
      std::string optstr =
        OptionParser::asString(opt, conf.getOption(opt));
      return cpp11::as_sexp(optstr);
    }
  }
  
  cpp11::stop("Uknown option '%s'. Check available options with `list_options()`", key.c_str());
}

void set_option_(Configurable & conf, const std::string & key,
                 const std::string & value) {
  const auto & opts = conf.getOptions();
  
  for (const auto& opt : opts) {
    if (key == OptEnum::_key(opt)) {
      i64 val = OptionParser::parse(opt, value);
      conf.setOption(opt, val);
      return;
    }
  }
  
  cpp11::stop("Uknown option '%s'. Check available options with `list_options()`", key.c_str());
}

[[cpp11::register]]
cpp11::list r_list_options_(int component_id,
                            cpp11::external_pointer<VAmiga> amiga,
                            int index) {
  return list_options_(configurable_from_id(component_id, amiga, index));
}

[[cpp11::register]]
cpp11::sexp r_get_option_(int component_id,
                          cpp11::external_pointer<VAmiga> amiga,
                          int index,
                          std::string key) {
  return (get_option_(configurable_from_id(component_id, amiga, index), key));
}

[[cpp11::register]]
void r_set_option_(int component_id,
                   cpp11::external_pointer<VAmiga> amiga,
                   int index,
                   std::string key, std::string value) {
  set_option_(configurable_from_id(component_id, amiga, index), key, value);
  return;
}
