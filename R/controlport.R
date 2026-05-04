#' @title The RamigaControlPort R6 Class
#' @description
#' A class that represents the emulator's control ports
#' (for mouse and joystick).
#' @include documentation.R
#' @export
RamigaControlPort <-
  R6::R6Class(
    "RamigaControlPort",
    inherit = RamigaComponent,
    
    active = list(
      #' @field device This field tells you which device (mouse, joystick or none)
      #' is connected to the current port. Should be a [RamigaControlDevice]
      #' class object, or `NULL` if there is no device.
      device = function(value) {
        if (missing(value)) {
          private$dev
        } else {
          private$dev <- RamigaControlDevice$new(
            emulator = private$emulator,
            port_number = private$index,
            type = value)
        }
      }
    ),
    
    public = list(
      #' @param emulator `r doc_param_emulator("control port")`
      #' @param port_number The Amiga has two control ports. This
      #' number specifies which one we are using. Should be either
      #' 1 or 2.
      #' @param device Device connected to this port. An [RamigaControlDevice]
      #' class object or `NULL` if there is no device.
      initialize = function(emulator, port_number = 1L, device = NULL) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator
        private$pointer <- emulator$get_pointer()
        port_number <- as.integer(port_number)
        if (port_number < 1L || port_number > 2L)
          stop("`port_number` should be 1 or 2")
        private$index <- port_number
      },
      
      #' @description
      #' Print some basic information about the control port.
      #' @param ... Ignored
      print = function(...) {
        cat(sprintf("Control port %i; connected with ", private$index))
        cat(if (is.null(private$dev)) "nothing" else private$dev$print())
      }
    ),
    
    private = list(
      component_id = 4L,
      index = 1L,
      dev = NULL
    )
  )