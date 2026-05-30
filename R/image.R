#' @title The RamigaImage R6 Class
#' @description
#' A virtual device represented by an image.
#' @export
RamigaImage <-
  R6::R6Class(
    "RamigaImage",
    public = list(
      #' @description
      #' Initialise an image from a disk image file.
      #' @param path File pointing to disk image file.
      initialize = function(path) {
        xt <- tools::file_ext(path)
        
        .fun_p <- function(pointer, path) disk_image_(path)
        .fun_r <- function(pointer, data, ext = xt) {
          tf <- tempfile(fileext = paste0(".", ext))
          writeBin(data, tf)
          disk_image_(tf)
        }
        
        private$image <- .read_raw(NULL, path, .fun_p, .fun_r)
      },
      
      #' @description
      #' Get information about the image.
      #' @return Returns a named `list` with information
      info = function() image_info_(private$image),
      
      #' @description
      #' Get the size of the device represented by the image.
      #' @return Returns the size of the image in bytes.
      size = function() image_size_(private$image),

      #' @description
      #' Get the pointer to the image object in memory
      #' @param ... Ignored.
      #' @return Returns the `externalptr` pointing to the C++ class
      #' instance in memory.
      get_pointer = function(...) private$image,
      
      #' @description
      #' Determines if there is a file system present.
      #' @return Returns `logical` indicating if disk contains a file system.
      is_formatted = function() fs_is_formatted_(private$image),
      
      #' @description
      #' Get a file system from a virtual device if present
      #' @param ... Ignored.
      #' @return Returns a [RamigaFileSystem] class object
      get_file_system = function(...) {
        if (!self$is_formatted()) stop("Cannot get file system for unformatted device")
        RamigaFileSystem$new(self)
      },
      
      #' @description
      #' Print some basic information about the device
      #' @param ... Ignored.
      print = function(...) {
        sprintf(
          "%s: %s image %s",
          ifelse(self$is_formatted(),
                 sprintf("\"%s\"",
                         self$get_file_system()$get_volume_name()),
                 "Unformatted"),
          self$info()[["type"]],
          self$info()[["format"]]) |>
          cat()
      }
    ),
    
    private = list(
      image = NULL
    )
  )