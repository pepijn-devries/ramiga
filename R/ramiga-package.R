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

.read_raw <- function(ptr, path, fun_p, fun_r, ...) {
  tryCatch({
    fun_p(ptr, path)
  }, error = function(e) {
    con <- file(path, open = "rb")
    rom_dat <- NULL
    repeat {
      chunk <- readBin(con, "raw", 1024L)
      if (length(chunk) == 0) break
      rom_dat <- c(rom_dat, chunk)
    }
    close(con)
    fun_r(ptr, rom_dat)
  })
}