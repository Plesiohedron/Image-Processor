add_compile_options(-Ofast)

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
    test_image_processor
    test.cpp
    test_image_processor.cpp
    Parser/Parser.cpp
    Filters/Filters.cpp
    Filters/ImageProcessor.cpp
    ImageLoaders/ImageLoader.cpp
    ImageLoaders/BMPLoader.cpp
    Image/Image.cpp
    Exceptions/Exceptions.cpp
)
