files_to_clean <- list.files("src", pattern = "\\.(o|so|dll)$", recursive = TRUE, full.names = TRUE)
file.remove(files_to_clean)