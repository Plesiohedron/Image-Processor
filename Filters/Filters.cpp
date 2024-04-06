#include <cmath>

#include "Filters.h"

const Matrix filter::Sharpening::SHARPING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const Matrix filter::EdgeDetection::EDGE_DETECTION_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

void matrix::Apply(Image& image, const Matrix& matrix) {
    std::vector<Pixel> new_pixels_data(image.pixels_data.size(), {0.0f, 0.0f, 0.0f});

    int matrix_center = static_cast<int>(matrix.size()) / 2;
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            Pixel pixel{0.0f, 0.0f, 0.0f};

            for (int i = -matrix_center; i <= matrix_center; ++i) {
                int dy = i + y;
                for (int j = -matrix_center; j <= matrix_center; ++j) {
                    int dx = j + x;
                    const float weight = static_cast<float>(matrix[i + matrix_center][j + matrix_center]);
                    const Pixel image_pixel = image.GetPixel(dy, dx);

                    pixel.r += image_pixel.r * weight;
                    pixel.g += image_pixel.g * weight;
                    pixel.b += image_pixel.b * weight;
                }
            }

            new_pixels_data[image.width * y + x].r = std::min(1.0f, std::max(0.0f, pixel.r));
            new_pixels_data[image.width * y + x].g = std::min(1.0f, std::max(0.0f, pixel.g));
            new_pixels_data[image.width * y + x].b = std::min(1.0f, std::max(0.0f, pixel.b));
        }
    }

    image.pixels_data = std::move(new_pixels_data);
}

void filter::Crop::ApplyFilter(Image& image) {
    width_ = std::min(width_, image.width);
    height_ = std::min(height_, image.height);

    std::vector<Pixel> new_pixels_data(width_ * height_);

    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            new_pixels_data[width_ * (height_ - i - 1) + j] =
                image.pixels_data[image.width * (image.height - i - 1) + j];
        }
    }

    image.pixels_data = std::move(new_pixels_data);
    image.width = width_;
    image.height = height_;
}

void filter::Grayscale::ApplyFilter(Image& image) {
    for (auto& pixel : image.pixels_data) {
        pixel.r = pixel.g = pixel.b =
            CorrectionFactorR * pixel.r + CorrectionFactorG * pixel.g + CorrectionFactorB * pixel.b;
    }
}

void filter::Negative::ApplyFilter(Image& image) {
    for (auto& pixel : image.pixels_data) {
        pixel.r = 1.0f - pixel.r;
        pixel.g = 1.0f - pixel.g;
        pixel.b = 1.0f - pixel.b;
    }
}

void filter::Sharpening::ApplyFilter(Image& image) {
    matrix::Apply(image, SHARPING_MATRIX);
}

void filter::EdgeDetection::ApplyFilter(Image& image) {
    std::unique_ptr<ImageProcessor> grayscale_filter{new Grayscale{}};
    grayscale_filter->ApplyFilter(image);

    matrix::Apply(image, EDGE_DETECTION_MATRIX);

    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            if (image.pixels_data[image.width * i + j].r > threshold_) {
                image.pixels_data[image.width * i + j].r = image.pixels_data[image.width * i + j].g =
                    image.pixels_data[image.width * i + j].b = 1.0f;
            } else {
                image.pixels_data[image.width * i + j].r = image.pixels_data[image.width * i + j].g =
                    image.pixels_data[image.width * i + j].b = 0.0f;
            }
        }
    }
}

void filter::GaussianBlur::ApplyFilter(Image& image) {
    std::vector<Pixel> temp_pixel_data(image.pixels_data.size(), {0.0f, 0.0f, 0.0f});

    const int kernel_radius = static_cast<int>(accuracy_ * sigma_);
    float normalization_factor = 0.0f;

    for (int i = -kernel_radius; i <= kernel_radius; ++i) {
        gaussian_blur_kernel_.push_back(GaussFunction(i));
        normalization_factor += gaussian_blur_kernel_.back();
    }

    for (int i = 0; i <= 2 * kernel_radius; ++i) {
        gaussian_blur_kernel_[i] /= normalization_factor;
    }

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            Pixel pixel{0.0f, 0.0f, 0.0f};

            for (int i = -kernel_radius; i <= kernel_radius; ++i) {
                const int dx = x + i;
                const float weight = gaussian_blur_kernel_[i + kernel_radius];
                const Pixel image_pixel = image.GetPixel(y, dx);

                pixel.r += image_pixel.r * weight;
                pixel.g += image_pixel.g * weight;
                pixel.b += image_pixel.b * weight;
            }

            temp_pixel_data[image.width * y + x] = pixel;
        }
    }

    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {
            Pixel pixel{0.0f, 0.0f, 0.0f};

            for (int i = -kernel_radius; i <= kernel_radius; ++i) {
                const int dy = std::max(0, std::min(y + i, image.height - 1));
                const float weight = gaussian_blur_kernel_[i + kernel_radius];
                const Pixel image_pixel = temp_pixel_data[image.width * dy + x];

                pixel.r += image_pixel.r * weight;
                pixel.g += image_pixel.g * weight;
                pixel.b += image_pixel.b * weight;
            }

            image.pixels_data[image.width * y + x] = pixel;
        }
    }
}

float filter::GaussianBlur::GaussFunction(const int dx) const {
    const float sigma_squared_doubled = 2.0f * sigma_ * sigma_;

    return std::pow(static_cast<float>(M_E), -static_cast<float>(dx * dx) / sigma_squared_doubled) /
           std::sqrt(static_cast<float>(M_PI) * sigma_squared_doubled);
}

void filter::Crystallize::ApplyFilter(Image& image) {
    crystals_count_ = std::min(crystals_count_, std::min(image.width, image.height));
    GenerateRandomCrystalCenters(image);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            image.pixels_data[image.width * y + x] = FindNearestCrystalCenter(y, x);
        }
    }
}

void filter::Crystallize::GenerateRandomCrystalCenters(const Image& image) {
    std::mt19937 generator{std::random_device{}()};
    std::uniform_int_distribution<> random_y(0, image.height - 1);
    std::uniform_int_distribution<> random_x(0, image.width - 1);

    for (int i = 0; i < crystals_count_; ++i) {
        int y = random_y(generator);
        int x = random_x(generator);
        Pixel pixel = image.pixels_data[image.width * y + x];

        crystal_centers_.push_back(std::tuple{y, x, pixel});
    }
}

Pixel filter::Crystallize::FindNearestCrystalCenter(const int y, const int x) const {
    float min_distance_squared = std::numeric_limits<float>::max();
    Pixel pixel{0.0f, 0.0f, 0.0f};

    for (auto [y_crystal, x_crystal, crystal_pixel] : crystal_centers_) {
        float distance = static_cast<float>((y - y_crystal) * (y - y_crystal) + (x - x_crystal) * (x - x_crystal));

        if (distance < min_distance_squared) {
            min_distance_squared = distance;
            pixel = crystal_pixel;
        }
    }

    return pixel;
}
