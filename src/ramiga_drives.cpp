#include <filesystem>
#include "ramiga_types.h"

void check_disk(cpp11::external_pointer<DiskImage> image) {
  if (!image) cpp11::stop("Disk image is no longer valid");
}

[[cpp11::register]]
void insert_disk_into_(cpp11::external_pointer<VAmiga> amiga, 
                       cpp11::external_pointer<DiskImage> image,
                       bool write_protected, int drive_number) {
  check_amiga(amiga);
  check_disk(image);
  
  FloppyDrive* drive = nullptr;
  
  switch(drive_number) {
  case 0: drive = &amiga->amiga.amiga->df0; break;
  case 1: drive = &amiga->amiga.amiga->df1; break;
  case 2: drive = &amiga->amiga.amiga->df2; break;
  case 3: drive = &amiga->amiga.amiga->df3; break;
  default: cpp11::stop("Invalid drive number");
  }
  
  if (!drive) cpp11::stop("Failed to access requested drive");
  
  auto* floppy_image = dynamic_cast<retro::vault::FloppyDiskImage*>(image.get());
  
  if (!floppy_image) {
    cpp11::stop("The provided image is not a valid floppy disk image.");
  }
  
  drive->insertImage(*floppy_image, write_protected);
}

[[cpp11::register]]
cpp11::external_pointer<DiskImage> floppy_disk_(std::string path) {
  std::filesystem::path p(path);
  auto disk = DiskImage::tryMake(p);
  
  if (!disk) {
    cpp11::stop("Failed to load disk image: %s", path.c_str());
  }
  
  return cpp11::external_pointer<DiskImage>(disk.release());
}
