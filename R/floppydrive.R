#' @title The RamigaFlopyDrive R6 Class
#' @description
#' A class that represents the emulator's floppy drive.
#' @include documentation.R
#' @export
RamigaFloppyDrive <-
  R6::R6Class(
    "RamigaFloppyDrive",
    public = list(
      #' @param emulator `r doc_param_emulator("floppy drive")`
      #' @param drive_number `r doc_param_drivenum()`
      initialize = function(emulator, drive_number = 0) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator$get_pointer()
        drive_number <- as.integer(drive_number)
        if (drive_number < 0L || drive_number > 3L)
          stop("`drive_number` should be between 0 and 3")
        private$drive_number <- drive_number
      },
      
      #' @description
      #' Insert a virtual floppy disk in the virtual floppy drive.
      #' @param disk A floppy disk represented by a [RamigaImage] class
      #' object.
      #' @param write_protected `logical` value indicating whether the
      #' inserted disk needs to be write protected. Default is `TRUE`
      insert_disk = function(disk, write_protected = TRUE) {
        stopifnot(inherits(disk, "RamigaImage"))
        insert_disk_into_(private$emulator, disk$get_pointer(),
                          write_protected, private$drive_number)
        self
      },
      
      #' @description
      #' Eject a virtual floppy disk from the virtual drive
      #' @param delay Delay for ejecting the disk counted in CPU cycles.
      eject_disk = function(delay = 0) {
        eject_disk_(private$emulator, private$drive_number, as.integer(delay))
        self
      },
      
      #' @description
      #' Get information about the floppy drive
      #' @return Returns a named list with information
      get_info = function() {
        fdrive_info_(private$emulator, private$drive_number)
      },
      
      #' @description
      #' Prints some basic information about the floppy drive
      #' @param ... Ignored
      print = function(...) {
        info <- self$get_info()
        sprintf("DF%i: %s",
                private$drive_number,
                ifelse(info$has_disk, "With disk", "Empty")) |>
          cat()
      }
    ),
    
    private = list(
      emulator = NULL,
      drive_number = 0
    )
  )