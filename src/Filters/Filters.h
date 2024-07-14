#pragma once

#include <memory>
#include <random>
#include <unordered_map>
#include <thread>

#include "ImageProcessor.h"

using Matrix = std::vector<std::vector<int>>;
namespace matrix {

void Apply(Image& image, const Matrix& matrix);

}  // namespace matrix

namespace filter {

class Crop : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;
    inline Crop(const int width, const int height) : width_{width}, height_{height} {};

protected:
    int width_;
    int height_;
};

class Grayscale : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;

private:
    static constexpr float CorrectionFactorR = 0.299f;
    static constexpr float CorrectionFactorG = 0.587f;
    static constexpr float CorrectionFactorB = 0.114f;
};

class Negative : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;
};

class Sharpening : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;

protected:
    static const Matrix SHARPING_MATRIX;
};

class EdgeDetection : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;
    inline explicit EdgeDetection(const float threshold) : threshold_{threshold} {};

protected:
    const float threshold_;
    static const Matrix EDGE_DETECTION_MATRIX;
};

class GaussianBlur : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;
    inline explicit GaussianBlur(const float sigma) : sigma_{sigma} {};

protected:
    const float accuracy_ = 3.0f;
    const float sigma_;
    std::vector<float> gaussian_blur_kernel_;

    float GaussFunction(const int dx) const;
};

class Crystallize : public ImageProcessor {
public:
    void ApplyFilter(Image& image) override;
    inline explicit Crystallize(const int crystals_count) : crystals_count_{crystals_count} {};

private:
    static constexpr int THREADS_COUNT_ = 6;

    std::vector<std::thread> threads_;
    std::vector<std::pair<int, int>> arguments_list_;

    void ThreadFunction(Pixel* pixels_start_data_pointer, const int image_width, const int pixels_data_start, const int pixels_data_size);

protected:
    int crystals_count_;
    std::vector<std::tuple<int, int, Pixel>> crystal_centers_;

    void GenerateRandomCrystalCenters(const Image& image);
    Pixel FindNearestCrystalCenter(const int y, const int x) const;
};

}  // namespace filter
