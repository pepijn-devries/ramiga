#' Save audio to WAV file
#' 
#' Helper function to write stereo audio to a WAV file.
#' @param samples A `matrix` of `double` values.
#' Values need to be between -1 and +1. The matrix needs to have
#' 2 rows. One for each channel.
#' @param path Path of the file where the audio needs to be stored
#' @param rate Sample rate. Defaults to 44100L
#' @returns Nothing
#' @export
save_wav <- function(samples, path, rate = 44100L) {
  save_wav_(samples, path, rate)
}