#pragma once

#include <filesystem>
#include <fstream>

#include "ImageLoader.h"
#include "../Exceptions/Exceptions.h"

#pragma pack(push, 1)
struct BMPHeader {
    const char signature[2]{'B', 'M'};
    uint32_t file_size;
    const uint16_t reserved1 = 0;
    const uint16_t reserved2 = 0;
    const uint32_t data_offset = 54;
    const uint32_t header_size = 40;
    int32_t width;
    int32_t height;
    const uint16_t planes = 1;
    const uint16_t bits_per_pixel = 24;
    const uint32_t compression = 0;
    uint32_t image_size;
    const int32_t x_pixels_per_meter = 2835;
    const int32_t y_pixels_per_meter = 2835;
    const uint32_t total_colors = 0;
    const uint32_t important_colors = 0;
};
#pragma pack(pop)

class BMPImageLoader : public ImageLoader {
public:
    Image ImportImage(const std::string& importing_path) const override;
    void ExportImage(const std::string& exporting_path, const Image& image) const override;

private:
    static const int CHANNELS_COUNT = 3;
    static constexpr float MaxColorValue = 255.0f;
};
