#' @title The RamigaEmulator R6 Class
#' @description
#' A class representing the emulator for emulating an Amiga.
#' @export
RamigaEmulator <-
  R6::R6Class(
    "RamigaEmulator",
    public = list(
      
      #' @description
      #' Initialise a new Amiga emulator
      initialize = function() private$emulator <- create_amiga_(),
      
      #' @description
      #' Get a representation of the machine's emulated memory
      #' @return Returns a [RamigaMemory] class object
      get_memory = function() RamigaMemory$new(self),

      #' @description
      #' Get a representation of the machine's Central Processing Unit
      #' @return Returns a [RamigaCPU] class object.
      get_cpu = function() RamigaCPU$new(self),
      
      #' @description
      #' Get a specific floppy drive from the emulated machine
      #' @param drive_number `r doc_param_drivenum()`
      #' @return Returns a [RamigaFloppyDrive] class object.
      get_floppy_drive = function(drive_number)
        RamigaFloppyDrive$new(self, drive_number),

      #' @description
      #' When the emulator is initialised it is powered off.
      #' Call this to power on the virtual machine.
      #' @return Returns the emulator object
      power_on = function() {
        poweron_amiga_(private$emulator)
        Sys.sleep(0.1)
        self
      },
      
      #' @description
      #' Power off emulator. Advisable if you plan to make adjustments
      #' to the emulated hardware configuration.
      #' @return Returns the emulator object
      power_off = function() {
        poweroff_amiga_(private$emulator)
        Sys.sleep(0.1)
        self
      },

      #' @description
      #' A soft reset, just resets the CPU, causing the system to reboot.
      #' This is similar to simultaneously pressing <Ctrl> and both
      #' <Amiga> keys on an original machine.
      #' @return Returns the emulator object
      soft_reset = function() {
        softreset_amiga_(private$emulator)
        Sys.sleep(0.1)
        self
      },
      
      #' @description
      #' When initialised, the emulator is paused. Call this to start
      #' running the virtual machine. It will hold up the R thread
      #' untill you interrupt (by pressing <ESC>). After the interrupt
      #' the machine will be paused.
      #' @return Returns NULL invisibly.
      run = function() {
        run_until_interrupted_(private$emulator)
        invisible()
      },
      
      #' @description
      #' Get information about the emulator state.
      #' @return Returns a named list.
      get_info = function() emulator_info_(private$emulator),
      
      #' @description
      #' Get the pointer to the emulator object in memory
      #' @param ... Ignored
      #' @return Returns the `externalptr` pointing to the C++ class
      #' instance in memory
      get_pointer = function(...) private$emulator,
      
      #' @description
      #' Get object to capture emulator output.
      #' @param ... Ignored
      #' @return Returns [RamigaOutput] class object
      get_output = function(...) RamigaOutput$new(self),
      
      #' @description
      #' @param ... Ignored
      #' Prints basic information about the emulator.
      print = function(...) {
        info <- self$get_info()
        cat(sprintf("Amiga emulator powered %s:\n  ",
                    ifelse(info[["powered"]], "on", "off")))
        self$get_info()
        self$get_cpu()$print()
        cat("\n  ")
        self$get_memory()$print()
      }  
    ),
    
    private = list(
      emulator = NULL
    )
  )