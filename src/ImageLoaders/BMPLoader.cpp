#include "BMPLoader.h"

#include <cstring>
#include <iostream>

Image BMPImageLoader::ImportImage(const std::string& importing_path) const {
    std::ifstream importing_file(importing_path, std::ios::in | std::ios::binary);

    if (!importing_file.is_open()) {
        throw LoaderError{"Failed to import file!"};
    }

    BMPHeader header;
    importing_file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    const int image_width = header.width;
    const int image_height = header.height;
    const int padding_per_row = (4 - (image_width * CHANNELS_COUNT) % 4) % 4;

    std::vector<Pixel> image_data(image_width * image_height, {0, 0, 0});

    for (int padding_column = 1; auto& pixel : image_data) {
        unsigned char color[3]{};
        importing_file.read(reinterpret_cast<char*>(color), CHANNELS_COUNT);

        pixel.r = static_cast<float>(color[2]) / MaxColorValue;
        pixel.g = static_cast<float>(color[1]) / MaxColorValue;
        pixel.b = static_cast<float>(color[0]) / MaxColorValue;

        if (padding_column % image_width == 0) {
            importing_file.ignore(padding_per_row);
        }
        ++padding_column;
    }

    importing_file.close();

    return Image{image_width, image_height, image_data};
}

void BMPImageLoader::ExportImage(const std::string& exporting_path, const Image& image) const {
    std::filesystem::path parent_path = std::filesystem::path(exporting_path).parent_path();

    if (!parent_path.empty()) {
        if (!std::filesystem::exists(parent_path) || !std::filesystem::is_directory(parent_path)) {
            std::filesystem::create_directories(parent_path);
        }
    }
    std::ofstream exporting_file(exporting_path, std::ios::out | std::ios::binary);

    if (!exporting_file.is_open()) {
        throw LoaderError{"Failed to export file!"};
    }

    const int padding_per_row = (4 - (image.width * CHANNELS_COUNT) % 4) % 4;
    unsigned char padding[3] = {0, 0, 0};

    BMPHeader header;
    header.width = image.width;
    header.height = image.height;
    header.image_size = header.width * header.height * CHANNELS_COUNT;
    header.file_size = header.data_offset + (header.width * CHANNELS_COUNT + padding_per_row) * header.height;

    exporting_file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    for (int padding_column = 1; const auto& pixel : image.pixels_data) {
        unsigned char r = static_cast<unsigned char>(pixel.r * MaxColorValue);
        unsigned char g = static_cast<unsigned char>(pixel.g * MaxColorValue);
        unsigned char b = static_cast<unsigned char>(pixel.b * MaxColorValue);

        unsigned char color[3] = {b, g, r};

        exporting_file.write(reinterpret_cast<char*>(color), CHANNELS_COUNT);

        if (padding_column % image.width == 0) {
            exporting_file.write(reinterpret_cast<char*>(padding), padding_per_row);
        }
        ++padding_column;
    }

    exporting_file.close();
}
