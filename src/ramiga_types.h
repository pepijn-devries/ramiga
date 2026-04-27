#include <cpp11.hpp>
#include <config.h>
#include <VAmigaTypes.h>
#include <VAmiga.h>
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

using namespace vamiga;
using namespace cpp11::literals;

void check_amiga(cpp11::external_pointer<VAmiga> amiga);
void check_disk(cpp11::external_pointer<DiskImage> image);