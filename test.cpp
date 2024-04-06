#include <catch.hpp>

#include "image_processor_unit_tester.h"

TEST_CASE("ParserErrors") {
    // std::ostringstream options;
    // options << "-crop {width} {height} \t \t Crop image" << '\n';
    // options << "-gs \t \t \t \t Convert image to grayscale" << '\n';
    // options << "-neg \t \t \t \t Negative image's colors" << '\n';
    // options << "-sharp \t \t \t \t Increase image's sharpness" << '\n';
    // options << "-edge {threshold} \t \t Highlight image's borders" << '\n';
    // options << "-blur {sigma} \t \t \t Blur image" << '\n';
    // options << "-crystal {crystals count} \t Crystallize image" << std::endl;
    // std::string options_str = options.str();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // std::ostringstream no_options_error;
    // no_options_error << "Options" << '\n' << '\n';
    // no_options_error << options_str;
    // const char* no_options_error_command[] = {"./image_processor"};
    // REQUIRE(ImageProcess(1, no_options_error_command).str() == no_options_error.str());

    // // No options assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream input_error;
    input_error << "Wrong input!" << std::endl;
    const char* input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp", "/output/lenna_crop.bmp",
                                         "-crop"};

    Parser parser1{std::size(input_error_command), input_error_command, 3};
    std::ostringstream message1;
    try {
        parser1.Parse();
    } catch (const ParserError& error) {
        message1 << error.what() << std::endl;
    }
    REQUIRE(message1.str() == input_error.str());

    // Wrong input (too few arguments) assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream crop_width_input_error;
    crop_width_input_error << "Wrong crop width input!" << std::endl;
    const char* crop_width_input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
                                                    "/output/lenna_crop.bmp", "-crop", "aboba"};

    Parser parser2{std::size(crop_width_input_error_command), crop_width_input_error_command, 3};
    std::ostringstream message2;
    try {
        parser2.Parse();
    } catch (const ParserError& error) {
        message2 << error.what() << std::endl;
    }
    REQUIRE(message2.str() == crop_width_input_error.str());

    // Wrong crop width input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream crop_height_input_error;
    crop_height_input_error << "Wrong crop height input!" << std::endl;
    const char* crop_height_input_error_command[] = {
        "./image_processor", "./test_script/data/lenna.bmp", "/output/lenna_crop.bmp", "-crop", "800", "abacaba"};

    Parser parser3{std::size(crop_height_input_error_command), crop_height_input_error_command, 3};
    std::ostringstream message3;
    try {
        parser3.Parse();
    } catch (const ParserError& error) {
        message3 << error.what() << std::endl;
    }
    REQUIRE(message3.str() == crop_height_input_error.str());

    // Wrong crop height input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream threshold_input_error;
    threshold_input_error << "Wrong threshold input!" << std::endl;
    const char* threshold_input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
                                                   "/output/lenna_edge.bmp", "-edge", "trash"};

    Parser parser4{std::size(threshold_input_error_command), threshold_input_error_command, 3};
    std::ostringstream message4;
    try {
        parser4.Parse();
    } catch (const ParserError& error) {
        message4 << error.what() << std::endl;
    }
    REQUIRE(message4.str() == threshold_input_error.str());

    // Wrong threshold input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream sigma_input_error;
    sigma_input_error << "Wrong sigma input!" << std::endl;
    const char* sigma_input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
                                               "/output/lenna_blur.bmp", "-blur", ".."};

    Parser parser5{std::size(sigma_input_error_command), sigma_input_error_command, 3};
    std::ostringstream message5;
    try {
        parser5.Parse();
    } catch (const ParserError& error) {
        message5 << error.what() << std::endl;
    }
    REQUIRE(message5.str() == sigma_input_error.str());

    // Wrong sigma input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream crystals_count_input_error;
    crystals_count_input_error << "Wrong crystals count input!" << std::endl;
    const char* crystals_count_input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
                                                        "/output/lenna_crystal.bmp", "-crystal", "...as"};

    Parser parser6{std::size(crystals_count_input_error_command), crystals_count_input_error_command, 3};
    std::ostringstream message6;
    try {
        parser6.Parse();
    } catch (const ParserError& error) {
        message6 << error.what() << std::endl;
    }
    REQUIRE(message6.str() == crystals_count_input_error.str());

    // Wrong crystal count input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream filters_name_input_error;
    filters_name_input_error << "Wrong filter's name!" << std::endl;
    const char* filters_name_input_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
                                                      "/output/lenna_filter.bmp", "-filter"};

    Parser parser7{std::size(filters_name_input_error_command), filters_name_input_error_command, 3};
    std::ostringstream message7;
    try {
        parser7.Parse();
    } catch (const ParserError& error) {
        message7 << error.what() << std::endl;
    }
    REQUIRE(message7.str() == filters_name_input_error.str());

    // Wrong filter's name input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // const char* correct_input_command1[] = {"./image_processor", "./test_script/data/lenna.bmp",
    //                                         "./output/lenna_gs_neg.bmp", "-gs", "-neg"};

    // REQUIRE(ImageProcess(5, correct_input_command1).str() == "");

    // // Correct input check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // const char* correct_input_command2[] = {"./image_processor", "test_script/data/lenna.bmp", "output/lenna_edge.bmp",
    //                                         "-edge", "0.5"};

    // REQUIRE(ImageProcess(5, correct_input_command2).str() == "");

    // // Correct input check
}

TEST_CASE("LoaderError") {
    std::ostringstream import_file_error;
    import_file_error << "Failed to import file!" << std::endl;
    std::string importing_file1{"./test_script/data/lena.bmp"};

    BMPImageLoader image_loader1;
    std::ostringstream message1;
    try {
        image_loader1.ImportImage(importing_file1);
    } catch (const LoaderError& error) {
        message1 << error.what() << std::endl;
    }
    REQUIRE(message1.str() == import_file_error.str());

    // Wrong importing file name input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // std::string importing_file2{"test_script/data/lenna.bmp"};

    // BMPImageLoader image_loader2;
    // std::ostringstream message2;
    // try {
    //     image_loader2.ImportImage(importing_file2);
    // } catch (const LoaderError& error) {
    //     message2 << error.what() << std::endl;
    // }
    // REQUIRE(message2.str() == "");

    // // Correct importing file name input assert check

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostringstream export_file_error;
    export_file_error << "Failed to export file!" << std::endl;
    std::string exporting_file = "";

    BMPImageLoader image_loader3;
    std::vector<Pixel> image_data = {{0, 0, 0}};
    Image image{1, 1, image_data};
    std::ostringstream message3;
    try {
        image_loader3.ExportImage(exporting_file, image);
    } catch (const LoaderError& error) {
        message3 << error.what() << std::endl;
    }
    REQUIRE(message3.str() == export_file_error.str());

    // Wrong exporting file name input assert check
}

// TEST_CASE("FileFormatError") {
//     std::ostringstream importing_file_format_error;
//     importing_file_format_error << "Wrong importing file format!" << '\n';
//     importing_file_format_error << "BMP is supported." << std::endl;

//     std::ostringstream exporting_file_format_error;
//     exporting_file_format_error << "Wrong exporting file format!" << '\n';
//     exporting_file_format_error << "BMP is supported." << std::endl;

//     const char* importing_file_format_error_command[] = {"./image_processor", "/test_script/data/lenna.jpg",
//                                                          "/output/lenna.bmp"};
//     const char* exporting_file_format_error_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
//                                                          "/output/lenna.png"};

//     REQUIRE(ImageProcess(3, importing_file_format_error_command).str() == importing_file_format_error.str());
//     REQUIRE(ImageProcess(3, exporting_file_format_error_command).str() == exporting_file_format_error.str());

//     // Wrong file formats assert check

//     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//     const char* importing_file_format_command[] = {"./image_processor", "test_script/data/lenna.bmp",
//                                                    "./output/lenna.bmp"};
//     const char* exporting_file_format_command[] = {"./image_processor", "./test_script/data/lenna.bmp",
//                                                    "./output/lenna.bmp"};

//     REQUIRE(ImageProcess(3, importing_file_format_command).str() == "");
//     REQUIRE(ImageProcess(3, exporting_file_format_command).str() == "");

//     // Correct file formats check
// }

// TEST_CASE("BMPLoader") {
//     const std::vector<Pixel> expected_pixels_data{
//         {0, 0, 187.0f / 255.0f}, {0, 0, 187.0f / 255.0f}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 187.0f / 255.0f}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 187.0f / 255.0f}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 187.0f / 255.0f}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 187.0f / 255.0f}, {1, 0, 0}, {1, 0, 0}, {0, 0, 0},
//     };
//     const int expected_image_width = 5;
//     const int expected_image_height = 5;

//     std::string importing_file{"./test_script/data/TEST_CASE_flag.bmp"};

//     BMPImageLoader image_loader1;
//     Image image = image_loader1.ImportImage(importing_file);

//     bool is_same_pixel_values = true;
//     for (int i = 0; i < expected_image_width * expected_image_height; ++i) {
//         if (image.pixels_data[i].r != expected_pixels_data[i].r ||
//             image.pixels_data[i].g != expected_pixels_data[i].g ||
//             image.pixels_data[i].b != expected_pixels_data[i].b) {
//             is_same_pixel_values = false;
//             break;
//         }
//     }

//     bool result =
//         (image.width == expected_image_width && image.height == expected_image_height && is_same_pixel_values);
//     REQUIRE(result);

//     // Correct image reading check
// }

// TEST_CASE("EdgeDetection") {
//     const std::vector<Pixel> expected_pixels_data{
//         {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0},
//         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1},
//         {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {1, 1, 1}, {0, 0, 0},
//     };
//     const int expected_image_width = 5;
//     const int expected_image_height = 5;
//     const float threshold = 0.2;

//     std::string importing_file{"./test_script/data/TEST_CASE_flag.bmp"};

//     BMPImageLoader image_loader1;
//     Image image = image_loader1.ImportImage(importing_file);

//     std::unique_ptr<ImageProcessor> image_processor{new filter::EdgeDetection{threshold}};
//     image_processor->ApplyFilter(image);

//     bool is_same_pixel_values = true;
//     for (int i = 0; i < expected_image_width * expected_image_height; ++i) {
//         if (image.pixels_data[i].r != expected_pixels_data[i].r ||
//             image.pixels_data[i].g != expected_pixels_data[i].g ||
//             image.pixels_data[i].b != expected_pixels_data[i].b) {
//             is_same_pixel_values = false;
//             break;
//         }
//     }

//     bool result =
//         (image.width == expected_image_width && image.height == expected_image_height && is_same_pixel_values);
//     REQUIRE(result);

//     // Correct edge detection check
// }

// TEST_CASE("Sharpening") {
//     const std::vector<Pixel> expected_pixels_data{
//         {0, 0, 187.0f / 255.0f}, {0, 0, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
//         {0, 0, 187.0f / 255.0f}, {0, 0, 1}, {1, 0, 0}, {1, 0, 0}, {0, 0, 0},
//     };
//     const int expected_image_width = 5;
//     const int expected_image_height = 5;

//     std::string importing_file{"./test_script/data/TEST_CASE_flag.bmp"};

//     BMPImageLoader image_loader1;
//     Image image = image_loader1.ImportImage(importing_file);

//     std::unique_ptr<ImageProcessor> image_processor{new filter::Sharpening{}};
//     image_processor->ApplyFilter(image);

//     bool is_same_pixel_values = true;
//     for (int i = 0; i < expected_image_width * expected_image_height; ++i) {
//         if (image.pixels_data[i].r != expected_pixels_data[i].r ||
//             image.pixels_data[i].g != expected_pixels_data[i].g ||
//             image.pixels_data[i].b != expected_pixels_data[i].b) {
//             is_same_pixel_values = false;
//             break;
//         }
//     }

//     bool result =
//         (image.width == expected_image_width && image.height == expected_image_height && is_same_pixel_values);
//     REQUIRE(result);

//     // Correct sharpening check
// }
