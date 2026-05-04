#' @title The RamigaCPU R6 Class
#' @description
#' A class that represents the emulator's Central Processing Unit (CPU).
#' @include documentation.R
#' @export
RamigaCPU <-
  R6::R6Class(
    "RamigaCPU",
    
    inherit = RamigaComponent,
    
    public = list(

      #' @description
      #' Get the CPU cycle count since the emulator started
      #' @return Returns the count in number of cycles
      get_cycles = function() {
        get_cpu_cycles_(private$pointer)
      },

      #' @description
      #' Get the memory address of the currently running program
      #' @return On the Amiga memory addresses are mapped as 32 bit
      #' unsigned integers. As R doesn't support this type, it is
      #' returned as a `numeric` (double) value.
      get_program_counter = function() {
        get_cpu_pc_(private$pointer)
      },

      #' @description
      #' Get current CPU configuration details
      #' @return Returns a named list
      get_config = function() {
        get_cpu_config_(private$pointer)
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
      component_id = 1L
    )
  )