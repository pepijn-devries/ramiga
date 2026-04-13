#include <cpp11.hpp>
#include "config.h"
#include "VAmigaTypes.h"
#include "vAmiga.h"
#include "Amiga.h"
#include "Memory.h"
#include "utl/storage/Buffer.h"
#include "utl/wrappers/Backed.h"
#include "Denise.h"
#include "DeniseTypes.h"
#include "EmulatorTypes.h"
#include "DiskImage.h"
#include "FloppyDrive.h"

using namespace vamiga;

void check_amiga(cpp11::external_pointer<VAmiga> amiga);