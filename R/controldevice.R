#' @title The RamigaControlDevice R6 Class
#' @description
#' A class that represents control devices, like the mouse or joystick.
#' @include documentation.R
#' @export
RamigaControlDevice <-
  R6::R6Class(
    "RamigaControlDevice",
    inherit = RamigaComponent,

    public = list(
      #' @param emulator A virtual control device only is meaningful when connected
      #' to a virtual device. Therefore, you need an emulator ([RamigaEmulator])
      #' to connect the device to.
      #' @param port_number Port on the virtual machine to which the device is
      #' connected. Should be either port 1 or 2.
      #' @param type Type of device, should be either `"mouse"`, or `"joystick"`.
      initialize = function(emulator, port_number, type) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator
        private$pointer <- emulator$get_pointer()
        port_number <- as.integer(port_number)
        if (port_number < 1L || port_number > 2L)
          stop("`port_number` should be 1 or 2")
        private$index <- port_number
        private$type <- type
        if (type == "joystick") {
          private$device <- joystick_(private$pointer, private$index)
        } else if (type == "mouse") {
          private$device <- mouse_(private$pointer, private$index)
        } else {
          stop("Unknown device ", type)
        }
      },

      #' @description
      #' Prints some basic information about the control device
      #' @param ... Ignored
      print = function(...) {
        private$type |>
          cat()
      }
    ),
    
    private = list(
      index = 1L,
      device = NULL,
      type = NULL
    )
  )