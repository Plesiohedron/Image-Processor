#pragma once

#include <string>

#include "../Image/Image.h"

class ImageLoader {
public:
    virtual Image ImportImage(const std::string& importing_path) const = 0;
    virtual void ExportImage(const std::string& exporting_path, const Image& image) const = 0;

    virtual ~ImageLoader() = default;
};
