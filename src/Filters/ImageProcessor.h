#pragma once

#include "../Image/Image.h"

class ImageProcessor {
public:
    virtual void ApplyFilter(Image& image) = 0;
    virtual ~ImageProcessor() = default;
};
