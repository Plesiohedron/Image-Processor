#pragma once

#include <stdexcept>
#include <string>

class ParserError : public std::runtime_error {
public:
    explicit ParserError(const std::string& message) : std::runtime_error{message} {};
};

class LoaderError : public std::runtime_error {
public:
    explicit LoaderError(const std::string& message) : std::runtime_error{message} {};
};

class FileFormatError : public std::runtime_error {
public:
    explicit FileFormatError(const std::string& message) : std::runtime_error{message} {};
};
