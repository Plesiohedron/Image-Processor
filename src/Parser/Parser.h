#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "../Filters/Filters.h"
#include "../Exceptions/Exceptions.h"

class Parser {
public:
    Parser(const int argc, const char** argv, int argv_index) : argc{argc}, argv{argv}, argv_index{argv_index} {};

    std::unique_ptr<ImageProcessor> Parse();
    void Validate() const;

    static const std::unordered_map<std::string, std::function<std::unique_ptr<ImageProcessor>(Parser& parser)>>
        FILTERS;

    const int argc;
    const char** argv;
    int argv_index;
};

namespace function {

std::unique_ptr<ImageProcessor> Crop(Parser& parser);
std::unique_ptr<ImageProcessor> Gs(Parser& parser);
std::unique_ptr<ImageProcessor> Neg(Parser& parser);
std::unique_ptr<ImageProcessor> Sharp(Parser& parser);
std::unique_ptr<ImageProcessor> Edge(Parser& parser);
std::unique_ptr<ImageProcessor> Blur(Parser& parser);
std::unique_ptr<ImageProcessor> Crystal(Parser& parser);

}  // namespace function
