#include "Image.h"

Image::Image(const int image_width, const int image_height, const std::vector<Pixel>& image_data)
    : pixels_data(image_data), width(image_width), height(image_height) {
}

Pixel Image::GetPixel(int y, int x) const {
    y = std::max(0, std::min(y, height - 1));
    x = std::max(0, std::min(x, width - 1));

    return pixels_data[width * y + x];
}
