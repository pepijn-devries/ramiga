#' @title The RamigaFileSystem R6 Class
#' @description
#' Obtain the file system from a virtual device (if available), such that
#' you can interact with it.
#' @export
RamigaFileSystem <-
  R6::R6Class(
    "RamigaFileSystem",
    public = list(
      #' @description
      #' Attempt to access the file system on a device image if available
      #' @param image The virtual device (represented by a [RamigaImage]
      #' class object), from which the file system should be retrieved
      initialize = function(image) {
        if (!image$is_formatted()) stop("Can't get file system from unformatted `image`")
        private$image <- image$get_pointer()
      },
      
      #' @description
      #' Get the name of the volume of that contains the file system
      #' @return Returns the name of the volume
      get_volume_name = function() {
        fs_get_name_(private$image)
      },
      
      #' @description
      #' Get some traits of the file system.
      #' @param ... Ignored
      #' @return Returns a named `list` of file system traits.
      get_traits = function(...) {
        fs_get_traits_(private$image)
      },
      
      #' @description
      #' Prints basic info about the file system
      #' @param ... Ignored.
      print = function(...) {
        paste0("File system: ", self$get_traits()$dos) |>
          cat()
      }
    ),
    
    private = list(
      image = NULL
    )
  )