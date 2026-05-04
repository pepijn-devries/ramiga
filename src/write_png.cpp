#ifdef USE_ZLIB
#include "ramiga_types.h"
#include <zlib.h>

// Helper for PNG Big-Endian 32-bit integers
void write_be32(std::ostream& out, uint32_t val) {
  uint8_t bytes[4] = {
    static_cast<uint8_t>(val >> 24),
    static_cast<uint8_t>(val >> 16),
    static_cast<uint8_t>(val >> 8),
    static_cast<uint8_t>(val)
  };
  out.write(reinterpret_cast<char*>(bytes), 4);
}

void write_chunk(std::ostream& out, const char* type, const uint8_t* data, uint32_t len) {
  write_be32(out, len);
  out.write(type, 4);
  
  if (len > 0 && data != nullptr) {
    out.write(reinterpret_cast<const char*>(data), len);
  }
  
  uint32_t crc = crc32(0, reinterpret_cast<const uint8_t*>(type), 4);
  if (len > 0 && data != nullptr) {
    crc = crc32(crc, data, len);
  }
  write_be32(out, crc);
}

static std::vector<uint8_t> uncompressed_buf;
static std::vector<uint8_t> compressed_buf;

void save_png(const char* path, VideoPortAPI & vport, bool is_pal) {
  isize x1 = 4 * HBLANK_CNT;
  isize x2 = 4 * PAL::HPOS_CNT;
  isize y1 = is_pal ? PAL::VBLANK_CNT : NTSC::VBLANK_CNT;
  isize y2 = is_pal ? PAL::VPOS_CNT_SF : NTSC::VPOS_CNT_SF;
  
  uint32_t width = (uint32_t)(x2 - x1);
  uint32_t height = (uint32_t)(y2 - y1);
  const auto& texture = vport.getTexture();
  
  std::ofstream f(path, std::ios::binary);
  f.write("\x89PNG\r\n\x1a\n", 8);
  
  // 1. IHDR
  uint8_t ihdr[13];
  auto write_to_buf = [&](uint32_t val, int offset) {
    ihdr[offset] = val >> 24; ihdr[offset+1] = val >> 16;
    ihdr[offset+2] = val >> 8; ihdr[offset+3] = val;
  };
  write_to_buf(width, 0);
  write_to_buf(height, 4);
  ihdr[8] = 8; ihdr[9] = 6; ihdr[10] = 0; ihdr[11] = 0; ihdr[12] = 0;
  write_chunk(f, "IHDR", ihdr, 13);
  
  // 2. IDAT (Processing)
  size_t required_size = height * (width * 4 + 1);
  if (uncompressed_buf.size() < required_size) uncompressed_buf.resize(required_size);
  
  uint8_t* dst = uncompressed_buf.data();
  for (uint32_t y = 0; y < height; ++y) {
    *dst++ = 0; // Filter byte 0
    uint32_t row_offset = (y + (uint32_t)y1) * HPIXELS + (uint32_t)x1;
    for (uint32_t x = 0; x < width; ++x) {
      uint32_t p = (uint32_t)texture[row_offset + x];
      *dst++ = p & 0xFF;         // A
      *dst++ = (p >> 8) & 0xFF;  // B
      *dst++ = (p >> 16) & 0xFF; // G
      *dst++ = (p >> 24) & 0xFF; // R
    }
  }
  
  // 3. Fast Compression (Level 1)
  uLongf max_compressed_size = compressBound(required_size);
  if (compressed_buf.size() < max_compressed_size) compressed_buf.resize(max_compressed_size);
  
  z_stream strm;
  strm.zalloc = Z_NULL; strm.zfree = Z_NULL; strm.opaque = Z_NULL;
  
  // Initialize for maximum speed
  deflateInit(&strm, Z_BEST_SPEED); 
  
  strm.next_in = uncompressed_buf.data();
  strm.avail_in = required_size;
  strm.next_out = compressed_buf.data();
  strm.avail_out = compressed_buf.size();
  
  deflate(&strm, Z_FINISH);
  uint32_t final_compressed_len = (uint32_t)strm.total_out;
  deflateEnd(&strm);
  
  write_chunk(f, "IDAT", compressed_buf.data(), final_compressed_len);
  
  // 4. IEND
  write_chunk(f, "IEND", nullptr, 0);
}

#endif /* USE_ZLIB */