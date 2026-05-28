#include <cpp11.hpp>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <config.h>
#include <VAmigaTypes.h>
#include <VAmiga.h>
#include <VAmigaWrapper.h>
#include <Amiga.h>
#include <Memory.h>
#include <utl/storage/Buffer.h>
#include <utl/wrappers/Backed.h>
#include <Denise.h>
#include <DeniseTypes.h>
#include <EmulatorTypes.h>
#include <DiskImage.h>
#include <FloppyDrive.h>
#include <Devices/Volume.h>
#include <FileSystems/Amiga/FileSystem.h>
#include <FileSystems/Amiga/FSBlock.h>
#include <Amiga.h>
#include <AmigaTypes.h>
#include <Option.h>

#define RAMIGA_COMP_UNDEFINED -1
#define RAMIGA_COMP_EMULATOR 0
#define RAMIGA_COMP_CPU 1
#define RAMIGA_COMP_MEMORY 2
#define RAMIGA_COMP_FLOPPYDRIVE 3
#define RAMIGA_COMP_CONTROLPORT 4
#define RAMIGA_COMP_VIDEO 5
#define RAMIGA_COMP_AUDIO 6

using namespace vamiga;
using namespace cpp11::literals;

void check_amiga(cpp11::external_pointer<VAmigaWrapper> amiga);
void check_disk(cpp11::external_pointer<DiskImage> image);
double get_cpu_cycles_(cpp11::external_pointer<VAmigaWrapper> amiga);

#ifdef USE_ZLIB
void save_png(const char* path, VideoPortAPI & vport, bool is_pal);
#endif
