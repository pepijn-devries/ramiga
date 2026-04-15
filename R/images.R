#' TODO
#' @export
RamigaImage <-
  R6::R6Class(
    "RamigaImage",
    public = list(
      #' @description
      #' TODO
      #' @param path TODO
      initialize = function(path) private$image <- disk_image_(path),
      
      #' @description
      #' TODO
      #' @returns TODO
      info = function() image_info_(private$image),
      
      #' @description
      #' TODO
      #' @returns Returns the size of the image in bytes.
      size = function() image_size_(private$image),

      #' @description
      #' TODO
      #' @returns TODO.
      get_pointer = function() private$image,
      
      print = function(...) cat("TODO\n")
    ),
    private = list(
      image = NULL,
      ..hidden = "secret" #TODO
    )
  )