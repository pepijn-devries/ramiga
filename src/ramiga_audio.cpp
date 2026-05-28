#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>
#include "ramiga_types.h"

AudioPortAPI & get_audioport_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  check_amiga(amiga);
  return amiga->audioPort;
}

[[cpp11::register]]
void clear_audio_stream_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  auto port = get_audioport_(amiga);
  port.port->clear();
}

[[cpp11::register]]
cpp11::doubles_matrix<> stereo_audio_buffer_(cpp11::external_pointer<VAmigaWrapper> amiga) {
  auto port = get_audioport_(amiga);
  
  // Block the stream from concurrent access
  port.port->stream.mutex.lock();
  
  isize buf_size = port.port->stream.count();

  std::vector<float> left(buf_size, 0.0);
  std::vector<float> right(buf_size, 0.0);
  isize nread = port.copyStereo(left.data(), right.data(), buf_size);
  
  // Free the stream for concurrent access
  port.port->stream.mutex.unlock();
  
  if (nread != buf_size) cpp11::stop("Buffer mismatch");
  
  cpp11::writable::doubles_matrix result(2, nread);
  for (isize i = 0; i < nread; i++) {
    result(0, i) = left[i];
    result(1, i) = right[i];
  }

  return result;
}

template <typename T>
void write_binary_(std::ofstream& stream, const T& value) {
  stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

[[cpp11::register]]
void save_wav_(
    cpp11::external_pointer<VAmigaWrapper> amiga, std::string path,
    int sample_rate) {
  cpp11::doubles_matrix<> samples = stereo_audio_buffer_(amiga);
  int num_channels = samples.nrow();
  int num_samples = samples.ncol();
  
  if (num_channels != 2) {
    cpp11::stop("Input matrix must have exactly 2 rows (Row 1: Left, Row 2: Right).");
  }
  
  uint16_t bits_per_sample = 16; 
  uint32_t data_chunk_size = num_samples * num_channels * (bits_per_sample / 8);
  uint32_t file_size_minus_8 = 36 + data_chunk_size;
  uint32_t byte_rate = sample_rate * num_channels * (bits_per_sample / 8);
  uint16_t block_align = num_channels * (bits_per_sample / 8);
  
  std::ofstream wav_file(path, std::ios::binary);
  if (!wav_file.is_open()) {
    cpp11::stop("Failed to open or create the output file.");
  }
  
  wav_file.write("RIFF", 4);
  write_binary_(wav_file, file_size_minus_8);
  wav_file.write("WAVE", 4);
  
  wav_file.write("fmt ", 4);
  write_binary_(wav_file, uint32_t(16));
  write_binary_(wav_file, uint16_t(1));
  write_binary_(wav_file, uint16_t(num_channels));
  write_binary_(wav_file, uint32_t(sample_rate));
  write_binary_(wav_file, byte_rate);
  write_binary_(wav_file, block_align);
  write_binary_(wav_file, bits_per_sample);
  
  wav_file.write("data", 4);
  write_binary_(wav_file, data_chunk_size);
  
  for (int col = 0; col < num_samples; ++col) {
    for (int chan = 0; chan < 2; chan++) {
      double d = samples(chan, col);
      d = std::max(-1.0, std::min(1.0, d));
      int16_t samp = static_cast<int16_t>(d * 32767.0);
      write_binary_(wav_file, samp);
    }
  }
  
  wav_file.close();
  return;
}