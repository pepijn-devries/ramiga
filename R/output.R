#' @title The RamigaOutput R6 Class
#' @description
#' A class to capture output from the Amiga emulator ([RamigaEmulator] class).
#' @export
RamigaOutput <-
  R6::R6Class(
    "RamigaOutput",
    public = list(
      
      #' @description
      #' Initialise a new Amiga emulator output object
      initialize = function(emulator) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("Need an R6 RamigaEmulator class object to initialise")
        private$emulator <- emulator$get_pointer
      },
      
      #' @description
      #' Prints basic information about the emulator output.
      #' @param ... Ignored
      print = function(...) cat("TODO\n")
    ),
    
    private = list(
      emulator = NULL
    )
  )