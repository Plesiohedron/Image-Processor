#include "Parser.h"

const std::unordered_map<std::string, std::function<std::unique_ptr<ImageProcessor>(Parser& parser)>> Parser::FILTERS =
    {{"-crop", function::Crop}, {"-gs", function::Gs},     {"-neg", function::Neg},        {"-sharp", function::Sharp},
     {"-edge", function::Edge}, {"-blur", function::Blur}, {"-crystal", function::Crystal}};

std::unique_ptr<ImageProcessor> Parser::Parse() {
    if (auto it = FILTERS.find(argv[argv_index]); it != FILTERS.end()) {
        return FILTERS.at(argv[argv_index++])(*this);
    } else {
        throw ParserError{"Wrong filter's name!"};
    }
}

void Parser::Validate() const {
    if (argv_index >= argc) {
        throw ParserError{"Wrong input!"};
    }
}

std::unique_ptr<ImageProcessor> function::Crop(Parser& parser) {
    int crop_width = 0;
    int crop_height = 0;

    parser.Validate();

    std::istringstream iss{parser.argv[parser.argv_index]};
    iss >> std::noskipws >> crop_width;
    if (!iss.eof() || iss.fail() || crop_width <= 0) {
        throw ParserError{"Wrong crop width input!"};
    }
    ++parser.argv_index;

    parser.Validate();

    iss = std::istringstream{parser.argv[parser.argv_index]};
    iss >> std::noskipws >> crop_height;
    if (!iss.eof() || iss.fail() || crop_height <= 0) {
        throw ParserError{"Wrong crop height input!"};
    }
    ++parser.argv_index;

    return std::make_unique<filter::Crop>(crop_width, crop_height);
}

std::unique_ptr<ImageProcessor> function::Gs(Parser& parser) {
    return std::make_unique<filter::Grayscale>();
}

std::unique_ptr<ImageProcessor> function::Neg(Parser& parser) {
    return std::make_unique<filter::Negative>();
}

std::unique_ptr<ImageProcessor> function::Sharp(Parser& parser) {
    return std::make_unique<filter::Sharpening>();
}

std::unique_ptr<ImageProcessor> function::Edge(Parser& parser) {
    float threshold = NAN;

    parser.Validate();

    std::istringstream iss{parser.argv[parser.argv_index]};
    iss >> std::noskipws >> threshold;
    if (!iss.eof() || iss.fail()) {
        throw ParserError{"Wrong threshold input!"};
    }
    ++parser.argv_index;

    return std::make_unique<filter::EdgeDetection>(threshold);
}

std::unique_ptr<ImageProcessor> function::Blur(Parser& parser) {
    float sigma = NAN;

    parser.Validate();

    std::istringstream iss{parser.argv[parser.argv_index]};
    iss >> std::noskipws >> sigma;
    if (!iss.eof() || iss.fail()) {
        throw ParserError{"Wrong sigma input!"};
    }
    ++parser.argv_index;

    return std::make_unique<filter::GaussianBlur>(sigma);
}

std::unique_ptr<ImageProcessor> function::Crystal(Parser& parser) {
    int crystals_count = 0;

    parser.Validate();

    std::istringstream iss{parser.argv[parser.argv_index]};
    iss >> std::noskipws >> crystals_count;
    if (!iss.eof() || iss.fail() || crystals_count <= 0) {
        throw ParserError{"Wrong crystals count input!"};
    }
    ++parser.argv_index;

    return std::make_unique<filter::Crystallize>(crystals_count);
}
