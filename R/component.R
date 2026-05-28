#' @title The RamigaComponent R6 Class
#' @description
#' An abstract class to represent emulator components. Each of the emulator
#' components inherit from this class. It provides consistent access to and
#' control over component specific options.
#' @export
RamigaComponent <-
  R6::R6Class(
    "RamigaComponent",
    public = list(
      #' @description
      #' Most emulator components don't need to be initialised. It's simplest
      #' to create an emulator with `RamigaEmulator$new()`. All components
      #' can be accessed through the R6 object fields.
      #' @param emulator All emulator components should be part of an emulator.
      #' All components (except for the emulator itself) therefore needs the,
      #' initialised with an emulator.
      #' @param component_id Integer value used to identify different
      #' types of components.
      #' @param ... Ignored
      initialize = function(emulator, component_id, ...) {
        if (identical(class(self)[1], "RamigaComponent")) {
          stop("RamigaComponent is an abstract class and cannot be instantiated directly.")
        } else if (missing(emulator) || !inherits(emulator, "RamigaEmulator"))
          stop("The `emulator` argument should enherit from RamigaEmulator")
        private$emulator <- emulator
        private$pointer <- emulator$get_pointer()
        if (!missing(component_id)) private$component_id <- component_id
      },
      
      #' @description
      #' Get the pointer to the emulator object in memory
      #' @param ... Ignored
      #' @return Returns the `externalptr` pointing to the C++ class
      #' instance in memory
      get_pointer = function(...) private$pointer,

      #' @description
      #' Get associated emulator.
      #' @param ... Ignored
      #' @return Returns a [RamigaEmulator] class object
      #' instance in memory
      get_emulator = function(...) private$emulator,
      
      #' @description
      #' List available options for the emulator component. It shows the name
      #' of the option and indicates their intended value(s).
      #' @param ... Ignored
      #' @return Returns a named `list` with available options.
      list_options = function(...) {
        if (is.list(private$component_id)) {
          nms <- names(private$component_id)
          lapply(private$component_id, r_list_options_,
                 amiga = private$pointer, index = private$index) |>
            setNames(nms)
        } else {
          r_list_options_(private$component_id,
                          private$pointer,
                          private$index)
        }
      }
    ),
    
    active = list(
      #' @field options A named `list` of options. You can get and set
      #' all individual elements. Elements are always returned as
      #' `character`, but can be also be set as `numeric` or `logical`,
      #' depending on the specific option. Assignment values are always
      #' parsed by the vAmiga engine.
      options = function(value) {
        if (missing(value)) value <- NULL
        .opts <- function(cid, value, nms) {
          if (missing (value) || is.null(value)) {
            opts <- lapply(nms, r_get_option_,
                           component = cid,
                           amiga = private$pointer,
                           index = private$index) |>
              setNames(nms)
          } else {
            nms <- names(value)
            value <- lapply(value, \(x) if(is.logical(x)) tolower(x) else x)
            mapply(r_set_option_, key = nms, value = unlist(value),
                   MoreArgs = list(component = cid,
                                   amiga = private$pointer,
                                   index = private$index))
            self
          }
        }
        
        lop <- self$list_options()
        if (is.list(private$component_id)) {
          nms <- names(private$component_id)
          if (!missing(value) && !is.null(value) &&
              !setequal(names(value), nms))
            stop("'value' should name all required components")
          lapply(nms, \(nm) {
            .opts(private$component_id[[nm]], value[[nm]], names(lop[[nm]]))
          }) |>
            setNames(nms)
        } else {
          .opts(private$component_id, value, names(lop))
        }
      }
    ),
    
    private = list(
      component_id = -1L,
      index = 0L,
      emulator = NULL,
      pointer = NULL
    )
    
  )