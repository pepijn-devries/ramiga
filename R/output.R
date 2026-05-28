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
      #' @return If file is missing it returns a [grDevices::as.raster()] object.
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
      #' Capture the audio that is currently on the output buffer.
      #' While the emulator is running, audio is continuously generated
      #' and stored in a ring buffer. Use this function to collect data
      #' in this buffer. It can only be read once and the buffer has
      #' a limited capacity.
      #' @param file A file path to store the audio (RIFF wav format).
      #' @param ... Ignored
      #' @return If file is omitted, the audio data is returned as
      #' a `matrix` of `numeric` values. It returns 2 rows (for both
      #' stereo channels). The number of columns correspond with the
      #' number of samples available from the buffer. The waveform
      #' is scaled between -1 and +1, such that it can be played
      #' directly with `audio::play()`.
      capture_audio_buffer = function(file, ...) {
        if (missing(file)) {
          stereo_audio_buffer_(private$pointer)
        } else {
          save_wav_(private$pointer, file, 44100L)
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