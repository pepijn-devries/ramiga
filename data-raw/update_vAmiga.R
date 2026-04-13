## Downloading source from repo: ------------------

message("Downloading vAmiga...")
repo_zip <- "https://github.com/dirkwhoffmann/vAmiga/archive/refs/tags/v4.4b12.zip"
temp_zip <- tempfile(fileext = ".zip")
temp_dir <- tempdir()
target_dir <- "src/vAmiga"

download.file(repo_zip, temp_zip, mode = "wb", method = "libcurl")
unzip(temp_zip, exdir = temp_dir)

extracted_path <- list.dirs(temp_dir, recursive = FALSE, full.names = TRUE)
extracted_path <- extracted_path[grep("vAmiga", extracted_path)]

## Patching downloaded files: ------------------

### Remove all specific files that are in this list: --------
files_to_delete <- readLines("data-raw/files_to_delete.txt")
unlink(file.path(extracted_path, files_to_delete))

all_dirs <- list.dirs(extracted_path, full.names = TRUE, recursive = TRUE)
empty_dirs <- all_dirs[
  sapply(all_dirs, function(x) {
    length(list.files(x, all.files = FALSE, full.names = TRUE)) == 0
  })
]
unlink(empty_dirs, recursive = TRUE, force = TRUE)
all_dirs <- list.dirs(extracted_path, recursive = FALSE)

### Remove all directories that are not "Core": ---------------
unlink(all_dirs[!endsWith(all_dirs, "Core")], recursive = TRUE, force = TRUE)

### Loop remaining files and patch them if needed: ----------------

all_files <- list.files(extracted_path, recursive = TRUE, full.names = TRUE)
file_patches <- list.files("data-raw/patch_files/", full.names = TRUE)

if (Sys.which("patch") == "") stop("You need to have 'patch' installed")
if (Sys.which("dos2unix") == "") stop("You need to have 'dos2unix' installed")

for (fl in file_patches) {
  source <-
    list.files(extracted_path,
               paste0("^", gsub("\\.diff$", "", basename(fl))),
               recursive = TRUE, full.names = TRUE) |>
    shQuote()
  difffl <- fl |> shQuote()
  system(sprintf("dos2unix %s", source))
  system(sprintf("dos2unix %s", difffl))
  system(
    sprintf("patch -i %s %s",
            difffl, source))
}

## Copying patched file to project: ------------------

if (dir.exists(target_dir)) unlink(target_dir, recursive = TRUE, force = TRUE)
dir.create(target_dir)

file.copy(
  list.files(extracted_path, full.names = TRUE),
  target_dir, recursive = TRUE)

unlink(temp_zip)
unlink(extracted_path, recursive = TRUE)
message("Update complete!")
