set(CXX_STANDARD 20)

add_executable(
    image_processor
    image_processor.cpp
    Parser/Parser.cpp
    Filters/Filters.cpp
    Filters/ImageProcessor.cpp
    ImageLoaders/ImageLoader.cpp
    ImageLoaders/BMPLoader.cpp
    Image/Image.cpp
    Exceptions/Exceptions.cpp
)

add_catch(
    image_processor_unit_tester
    test.cpp
    image_processor_unit_tester.cpp
    Parser/Parser.cpp
    Filters/Filters.cpp
    Filters/ImageProcessor.cpp
    ImageLoaders/ImageLoader.cpp
    ImageLoaders/BMPLoader.cpp
    Image/Image.cpp
    Exceptions/Exceptions.cpp
)
