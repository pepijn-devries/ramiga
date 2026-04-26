#' @title The RamigaMemory R6 Class
#' @description
#' The RamigaMemory class represents the memory of the emulated machine.
#' Use this object to interact with the machines memory.
#' @export
RamigaMemory <-
  R6::R6Class(
    "RamigaEmulator",
    public = list(
      #' @description
      #' The memory needs to be associated with an emulated machine.
      #' Therefore you need the emulator to initiate a memory object.
      #' @param emulator `r doc_param_emulator("memory")`
      initialize = function(emulator) {
        if (!inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator$get_pointer()
      },
      
      #' @description
      #' Load an operating system to ROM. It can be an official Kickstart
      #' ROM image, or the rom provided for AROS Research Operating System.
      #' @param path File path pointing to the location of the ROM file.
      #' @return Returns the updated RamigaMemory object.
      load_rom = function(path) {
        load_rom_(private$emulator, path)
        self
      },
      
      #' @description
      #' Check if a ROM image was successfully loaded
      #' @return Returns a `logical` value.
      has_rom = function() {
        has_rom_(private$emulator)
      },
      
      #' @description
      #' Get ROM characteristics if known.
      #' @return Returns `NULL` if no ROM has been loaded. It will return
      #' A named list with ROM traits otherwise.
      get_rom_traits = function() {
        if (self$has_rom()) get_rom_traits_(private$emulator) else NULL
      },

      #' @description
      #' Get details on the configuration of the emulated memory
      #' @return Returns a named `list` with memory configurations.
      get_config = function() get_mem_config_(private$emulator),
      
      #' @description
      #' Print some basic information about the emulated memory.
      #' @param ... Ignored.
      print = function(...) {
        config <- self$get_config()
        sprintf("Memory: chip %.1fMb; slow %.1fMb; fast %.1fMb; ROM: %s",
                config$chip_size/1048576,
                config$slow_size/1048576,
                config$fast_size/1048576,
                ifelse(self$has_rom(),
                       self$get_rom_traits()$title,
                       "Not loaded")) |>
          cat()
      }
    ),
    private = list(
      emulator = NULL
    )
  )