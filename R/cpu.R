#' @title The RamigaCPU R6 Class
#' @description
#' A class that represents the emulator's Central Processing Unit (CPU).
#' @include documentation.R
#' @export
RamigaCPU <-
  R6::R6Class(
    "RamigaCPU",
    public = list(
      #' @description
      #' Initialise a RamigaCPU class object.
      #' @param emulator `r doc_param_emulator("CPU")`
      initialize = function(emulator) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator$get_pointer()
      },
      
      #' @description
      #' Get the CPU cycle count since the emulator started
      #' @return Returns the count in number of cycles
      get_cycles = function() {
        get_cpu_cycles_(private$emulator)
      },

      #' @description
      #' Get the memory address of the currently running program
      #' @return On the Amiga memory addresses are mapped as 32 bit
      #' unsigned integers. As R doesn't support this type, it is
      #' returned as a `numeric` (double) value.
      get_program_counter = function() {
        get_cpu_pc_(private$emulator)
      },

      #' @description
      #' Get current CPU configuration details
      #' @return Returns a named list
      get_config = function() {
        get_cpu_config_(private$emulator)
      },
      
      #' @description
      #' Print some basic information about the CPU
      #' @param ... Ignored
      print = function(...) {
        sprintf("CPU: %s", self$get_config()$revision) |>
          cat()
      }
    ),
    private = list(
      emulator = NULL
    )
  )