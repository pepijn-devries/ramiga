#' @title The RamigaEmulator R6 Class
#' @description
#' A class representing the emulator for emulating an Amiga.
#' @export
RamigaEmulator <-
  R6::R6Class(
    "RamigaEmulator",
    
    inherit = RamigaComponent,
    
    active = list(
      #' @field memory The emulated memory, represented by [RamigaMemory]
      memory = function(value) {
        if (missing(value)) {
          RamigaMemory$new(self)
        } else {
          if (!(inherits(value, "RamigaMemory") &&
                identical(value$get_pointer(), self$get_pointer())))
            stop("Can only assign memory from shared emulator")
          self
        }
      },
      
      #' @field cpu The emulated CPU, represented by [RamigaCPU]
      cpu = function(value) {
        if (missing(value)) {
          RamigaCPU$new(self)
        } else {
          if (!(inherits(value, "RamigaCPU") &&
                identical(value$get_pointer(), self$get_pointer())))
            stop("Can only assign CPU from shared emulator")
          self
        }
      },
      
      #' @field floppy_drives The emulated floppy drives, represented by
      #' a named `list` of [RamigaFloppyDrive] objects.
      floppy_drives = function(value) {
        if (missing(value)) {
          lapply(0:3, \(x) RamigaFloppyDrive$new(self, x)) |>
            setNames(sprintf("DF%i", 0:3))
        } else {
          lapply(value, \(val) {
            if (!(inherits(val, "RamigaFloppyDrive") &&
                  identical(val$get_pointer(), self$get_pointer())))
              stop("Can only assign FloppyDrive from shared emulator")
          })
          self
        }
      },

      #' @field control_ports Control ports to which a virtual mouse or
      #' joystick can be connected. It is represented by the
      #' [RamigaControlPort] class.
      control_ports = function(value) {
        if (missing(value)) {
          private$cports
        } else {
          lapply(value, \(val) {
            if (!(inherits(val, "RamigaControlPort") &&
                  identical(val$get_pointer(), self$get_pointer())))
              stop("Can only assign RamigaControlPort from shared emulator")
          })
          if (!identical(names(value), sprintf("port%i", 1:2)))
            stop("Replacement port should have identical names")
          private$cports <- value
          self
        }
      },
      
      #' @field output Get object to capture emulator output. Handled
      #' by [RamigaOutput].
      output = function(value) RamigaOutput$new(self)
    ),
    
    public = list(
      
      #' @description
      #' Initialise a new Amiga emulator
      initialize = function() {
        private$pointer <- create_amiga_()
        private$emulator <- self
        ## These options are critical for proper
        ## audio recording
        self$output$options$audio$AUD.ASR <- FALSE
        self$output$options$audio$AUD.FASTPATH <- FALSE
        
        ## We need to keep track of the actual R-object as the
        ## C++ object is unaware of devices connected to the port
        private$cports <- lapply(1:2, \(x) RamigaControlPort$new(self, x)) |>
          setNames(sprintf("port%i", 1:2))
        private$cports$port1$device <- "mouse"
        private$cports$port2$device <- "joystick"
      },
      
      #' @description
      #' When the emulator is initialised it is powered off.
      #' Call this to power on the virtual machine.
      #' @return Returns the emulator object
      power_on = function() {
        poweron_amiga_(private$pointer)
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
      #' This is similar to simultaneously pressing \out{<Ctrl>} and both
      #' \out{<Amiga>} keys on an original machine.
      #' @return Returns the emulator object
      soft_reset = function() {
        softreset_amiga_(private$pointer)
        Sys.sleep(0.1)
        self
      },

      #' @description
      #' A hard reset. Same as powering of the machine, then powering
      #' it back on.
      #' @return Returns the emulator object
      hard_reset = function() {
        hardreset_amiga_(private$pointer)
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
        run_until_interrupted_(private$pointer)
        invisible()
      },
      
      #' @description
      #' Update the machines state to the next video frame. The machine
      #' runs until the vertical blank is reached and pauses imediately.
      #' @return Returns the emulator object
      next_frame = function() {
        update_screen_(private$pointer)
        self
      },
      
      #' @description
      #' Get information about the emulator state.
      #' @return Returns a named list.
      get_info = function() emulator_info_(private$pointer),

      #' @description
      #' Get information about the emulator configuration.
      #' @return Returns a named list.
      get_config = function() emulator_config_(private$pointer),

      #' @description
      #' Quickly set the emulator configuration to one of the pre-specified
      #' schemes.
      #' @param scheme Should be one of the following strings:
      #' `"A1000_OCS_1MB"`, `"A500_OCS_1MB"` (default), `"A500_ECS_1MB"`,
      #' or `"A500_PLUS_1MB"`.
      #' @param ... Ignored
      #' @return Returns a string
      set_config = function(scheme = "A500_OCS_1MB", ...) {
        emu_set_config_scheme_(private$pointer, scheme)
        Sys.sleep(0.1)
        self
      },

      #' @description
      #' Get the version number of the vAmiga core used by this package
      #' @param ... Ignored
      #' @return Returns a string
      get_version = function(...) emulator_version_(private$pointer),
      
      #' @description
      #' Prints basic information about the emulator.
      #' @param ... Ignored
      print = function(...) {
        info <- self$get_info()
        cat(sprintf("Amiga emulator (%s) powered %s:\n  ",
                    self$get_config()$tv,
                    ifelse(info[["powered"]], "on", "off")))
        self$get_info()
        self$cpu$print()
        cat("\n  ")
        self$memory$print()
      }  
    ),

    private = list(
      component_id = 0L,
      cports = NULL
    )
  )