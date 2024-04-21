#pragma once

#include <vector>

struct Pixel {
    float r, g, b;
};

class Image {
public:
    std::vector<Pixel> pixels_data;
    int width;
    int height;

public:
    Image(const int image_width, const int image_height, const std::vector<Pixel>& image_data);

    Pixel GetPixel(int y, int x) const;
};
