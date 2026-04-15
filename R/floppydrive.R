#' TODO
#' @export
RamigaFloppyDrive <-
  R6::R6Class(
    "RamigaFloppyDrive",
    public = list(
      #' @description
      #' TODO
      #' @param emulator TODO
      #' @param drive_number TODO
      initialize = function(emulator, drive_number = 0) {
        #TODO check emulator
        private$emulator <- emulator
        #TODO check drive_number
        private$drive_number <- drive_number
      },
      
      #' @description
      #' TODO
      #' @param disk TODO
      #' @param write_protected TODO
      insert_disk = function(disk, write_protected = TRUE) {
        stopifnot(inherits(disk, "RamigaImage"))
        insert_disk_into_(private$emulator, disk$get_pointer(),
                          write_protected, private$drive_number)
        self
      },
      
      #' @description
      #' TODO
      #' @param delay TODO
      eject_disk = function(delay = 0) {
        eject_disk_(as.integer(delay))
        self
      },
      
      #' @param disk TODO
      print = function(...) cat("TODO\n")
    ),
    
    private = list(
      emulator = NULL,
      drive_number = 0
    )
  )