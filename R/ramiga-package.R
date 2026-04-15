#' @keywords internal
"_PACKAGE"
NULL

.onUnload <- function(libpath) {
  library.dynam.unload("ramiga", libpath)
}

#' @importFrom R6 R6Class
NULL

## usethis namespace: start
#' @useDynLib ramiga, .registration = TRUE
## usethis namespace: end
NULL
