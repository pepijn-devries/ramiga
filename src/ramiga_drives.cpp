#include <filesystem>
#include "ramiga_types.h"

using namespace retro::vault;

void check_disk(cpp11::external_pointer<DiskImage> image) {
  if (!image) cpp11::stop("Disk image is no longer valid");
}

FloppyDrive& get_floppy_drive_(cpp11::external_pointer<VAmigaWrapper> amiga,
                               int drive_number) {
  check_amiga(amiga);
  if (drive_number < 0 || drive_number > 3)
    cpp11::stop("Invalid drive number");
  auto& drive = amiga->df[drive_number]->drive;
  if (!drive) cpp11::stop("Failed to access requested drive");
  return *drive;
}

[[cpp11::register]]
void insert_disk_into_(cpp11::external_pointer<VAmigaWrapper> amiga, 
                       cpp11::external_pointer<DiskImage> image,
                       bool write_protected, int drive_number) {
  check_disk(image);
  auto& drive = get_floppy_drive_(amiga, drive_number);
  auto* floppy_image = dynamic_cast<retro::vault::FloppyDiskImage*>(image.get());
  
  if (!floppy_image) {
    cpp11::stop("The provided image is not a valid floppy disk image.");
  }
  
  drive.insertImage(*floppy_image, write_protected);
}

[[cpp11::register]]
void eject_disk_(cpp11::external_pointer<VAmigaWrapper> amiga,
                 int drive_number, int delay) {
  auto& drive = get_floppy_drive_(amiga, drive_number);
  drive.ejectDisk(delay);
}

[[cpp11::register]]
cpp11::external_pointer<DiskImage> disk_image_(std::string path) {
  std::filesystem::path p(path);
  auto disk = DiskImage::tryMake(p);
  
  if (!disk) {
    cpp11::stop("Failed to load disk image" + path);
  }
  
  return cpp11::external_pointer<DiskImage>(disk.release());
}

[[cpp11::register]]
cpp11::list fdrive_info_(cpp11::external_pointer<VAmigaWrapper> amiga,
                            int drive_number) {
  check_amiga(amiga);
  auto& drive = get_floppy_drive_(amiga, drive_number);
  auto info = drive.cacheInfo();

  return cpp11::writable::list({
    "nr"_nm = cpp11::as_sexp(info.nr),
      "head_position"_nm = cpp11::as_sexp((int)info.head.track()),
      "is_donnected"_nm = cpp11::as_sexp(info.isConnected),
      "has_disk"_nm = cpp11::as_sexp(info.hasDisk),
      "has_modified_disk"_nm = cpp11::as_sexp(info.hasModifiedDisk),
      "has_protected_disk"_nm = cpp11::as_sexp(info.hasProtectedDisk),
      "has_unprotected_disk"_nm = cpp11::as_sexp(info.hasUnprotectedDisk),
      "motor_active"_nm = cpp11::as_sexp(info.motor),
      "is_writing"_nm = cpp11::as_sexp(info.writing)
  });
}

[[cpp11::register]]
cpp11::strings image_info_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  auto&& info = image->info();
  
  return cpp11::writable::strings({
    "type"_nm = ImageTypeEnum::_key(info.type),
      "format"_nm = ImageFormatEnum::_key(info.format)
  });
}

[[cpp11::register]]
double image_size_(cpp11::external_pointer<DiskImage> image) {
  check_disk(image);
  return (double)image->size();
}

