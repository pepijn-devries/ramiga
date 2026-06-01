# Save audio to WAV file

Helper function to write stereo audio to a WAV file.

## Usage

``` r
save_wav(samples, path, rate = 44100L)
```

## Arguments

- samples:

  A `matrix` of `double` values. Values need to be between -1 and +1.
  The matrix needs to have 2 rows. One for each channel.

- path:

  Path of the file where the audio needs to be stored

- rate:

  Sample rate. Defaults to 44100L

## Value

Nothing
