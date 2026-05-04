#' @title The RamigaOutput R6 Class
#' @description
#' A class to capture output from the Amiga emulator ([RamigaEmulator] class).
#' @export
RamigaOutput <-
  R6::R6Class(
    "RamigaOutput",
    inherit = RamigaComponent,
    
    public = list(

      #' @description
      #' Captures the current pixel information as sent to the monitor of
      #' the virtual device.
      #' @param file A path to a png file where to store the captured frame.
      #' @param ... Ignored
      #' @return If file is missing it returns a [grDevice::as.raster()] object.
      #' Otherwise, it will save it as png file to the specified path and returns
      #' nothing.
      capture_frame = function(file, ...) {
        if (missing(file)) {
          get_framebuffer_vport_(private$pointer) |>
            grDevices::as.raster()
        } else {
          save_framebuffer_(private$pointer, file)
        }
      },

      #' @description
      #' TODO
      #' @param file TODO
      #' @param ... TODO
      #' @return TODO
      capture_audio_buffer = function(file, ...) {
        if (missing(file)) {
          #TODO
        } else {
          #TODO
        }
      },
      
      #' @description
      #' Prints basic information about the emulator output.
      #' @param ... Ignored
      print = function(...) cat("TODO\n")
    ),
    
    private = list(
      component_id = list(video = 5L, audio = 6L),
      emulator = NULL
    )
  )