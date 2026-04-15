#' TODO
#' @export
RamigaMemory <-
  R6::R6Class(
    "RamigaEmulator",
    public = list(
      #' @description
      #' TODO
      #' @param emulator TODO
      initialize = function(emulator) {
        ## TODO check if it is actually an emulator (external pointer)
        private$emulator <- emulator
      },
      
      #' @description
      #' TODO
      #' @param path TODO
      #' @returns TODO
      load_rom = function(path) {
        load_rom_(private$emulator, path)
        self
      },
      
      #' @description
      #' TODO
      #' @returns TODO
      has_rom = function() {
        has_rom_(private$emulator)
      },
      
      print = function(...) cat("TODO\n")
    ),
    private = list(
      emulator = NULL
    )
  )