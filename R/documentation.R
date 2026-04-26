doc_param_emulator <- function(component) {
  paste(
    "An `RamigaEmulator` class object. The", component, "to be created needs",
    "to be associated with a virtual machine. The initiated object",
    "will represent the", component, "of the emulated machine."
  )
}

doc_param_drivenum <- function() {
  paste(
    "The emulator has 4 floppy drives,",
    "numbered 0 to 3. Pick which drive you want to operate"
  )
}
