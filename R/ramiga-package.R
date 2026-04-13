#' @keywords internal
"_PACKAGE"
NULL

.onUnload <- function(libpath) {
  library.dynam.unload("ramiga", libpath)
}

## usethis namespace: start
#' @useDynLib ramiga, .registration = TRUE
## usethis namespace: end
NULL
