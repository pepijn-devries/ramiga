#include "ramiga_types.h"

MemoryAPI & get_memory_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  return amiga->mem;
}

[[cpp11::register]]
void load_rom_(cpp11::external_pointer<VAmigaWrapper> amiga, std::string path) {
  get_memory_(amiga).loadRom(std::filesystem::path(path));
  return;
}

[[cpp11::register]]
void load_rom_ext_(cpp11::external_pointer<VAmigaWrapper> amiga, std::string path) {
  get_memory_(amiga).loadExt(std::filesystem::path(path));
  return;
}

[[cpp11::register]]
bool has_rom_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  return get_memory_(amiga).mem->hasRom();
}

[[cpp11::register]]
cpp11::list get_rom_traits_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  // return get_memory_(amiga).mem->hasRom();
  const RomTraits traits = get_memory_(amiga).getRomTraits();
  return cpp11::writable::list({
    "title"_nm = cpp11::writable::strings({(std::string)traits.title}),
      "revision"_nm = cpp11::writable::strings({(std::string)traits.revision}),
      "released"_nm = cpp11::writable::strings({(std::string)traits.released}),
      "model"_nm = cpp11::writable::strings({(std::string)traits.model})
  });
}

[[cpp11::register]]
cpp11::list get_mem_config_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  // return get_memory_(amiga).mem->hasRom();
  const auto conf = get_memory_(amiga).getConfig();
  return cpp11::writable::list({
    "chip_size"_nm = cpp11::as_sexp({(double)conf.chipSize}),
      "slow_size"_nm = cpp11::as_sexp({(double)conf.slowSize}),
      "fast_size"_nm = cpp11::as_sexp({(double)conf.fastSize}),
      "rom_size"_nm = cpp11::as_sexp({(double)conf.romSize}),
      "wom_size"_nm = cpp11::as_sexp({(double)conf.womSize}),
      "ext_size"_nm = cpp11::as_sexp({(double)conf.extSize}),
      "ext_start"_nm = cpp11::as_sexp({(double)conf.extStart}),
      "save_roms"_nm = cpp11::as_sexp({conf.saveRoms}),
      "slow_ram_delay"_nm = cpp11::as_sexp({conf.slowRamDelay}),
      "slow_ram_mirror"_nm = cpp11::as_sexp({conf.slowRamMirror}),
      "bank_map"_nm = cpp11::writable::strings({
        BankMapEnum::_key(conf.bankMap)}),
      "ram_init_pattern"_nm = cpp11::writable::strings({
        RamInitPatternEnum::_key(conf.ramInitPattern)}),
      "unmapping_type"_nm = cpp11::writable::strings({
        UnmappedMemoryEnum::_key(conf.unmappingType)})
  });
}
