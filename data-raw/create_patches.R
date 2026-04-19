dir_original_files <- "../backup/vAmiga_original"
dir_patched_files  <- "../backup/vAmiga_patched"
destination        <- "../backup/patch_files"

files_original <- list.files(dir_original_files, recursive = TRUE)
files_patched  <- list.files(dir_patched_files, recursive = TRUE)
files_to_delete <-
  files_original[!files_original %in% files_patched]
problematic_files <-
  files_patched[!files_patched %in% files_original]

if (Sys.which("diff") == "") stop("You need to have 'diff' installed")
for (fl in files_patched[files_patched %in% files_original]) {
  print(sprintf("Working on '%s'", fl))
  result <-
    system2(
      command = "diff", 
      args = c("-u",
               file.path(dir_original_files, fl) |> normalizePath() |>
                 shQuote(),
               file.path(dir_patched_files, fl) |> normalizePath() |>
                 shQuote()),
      stdout = TRUE
    )
  if (length(result) > 2) {
    result[[1]] <- "--- \"a\""
    result[[2]] <- "+++ \"b\""
    dest <- normalizePath(file.path(destination, dirname(fl)))
    if (!dir.exists(dest)) dir.create(dest, recursive = TRUE)
    writeLines(result, file.path(dest, paste0(basename(fl), ".diff")))
  }
}

writeLines(
  files_to_delete,
  "../backup/files_to_delete.txt"
)
