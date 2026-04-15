#' TODO
#' @export
RamigaEmulator <-
  R6::R6Class(
    "RamigaEmulator",
    public = list(
      
      #' @description
      #' TODO
      initialize = function() private$emulator <- create_amiga_(),
      
      #' @description
      #' TODO
      #' @returns TODO
      get_memory = function() RamigaMemory$new(private$emulator),
      
      #' @description
      #' TODO
      #' @param drive_number
      #' @returns TODO
      get_floppy_drive = function(drive_number)
        RamigaFloppyDrive$new(private$emulator, drive_number),

      #' @description
      #' TODO
      #' @returns TODO
      start = function() {start_amiga_(private$emulator); self },
      
      #' @description
      #' TODO
      #' @returns TODO
      run = function() { run_until_interrupted_(private$emulator); invisible() },
      
      #' @description
      #' TODO
      #' @returns TODO
      info = function() emulator_info_(private$emulator),
      
      #' @description
      #' TODO
      print = function(...) cat("TODO\n")
    ),
    private = list(
      emulator = NULL
    )
  )