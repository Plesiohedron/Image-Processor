#include "test_image_processor.h"

std::ostringstream ImageProcess(const int argc, const char* argv[]) {
    std::ostringstream message;

    try {
        if (argc == 1) {
            throw ParserError{"Options"};
        }

        Parser parser{argc, argv, 0};
        int& index = parser.argv_index;

        ++index;
        parser.Validate();
        const std::string importing_file{argv[index]};

        ++index;
        parser.Validate();
        const std::string exporting_file{argv[index]};

        if (!importing_file.ends_with(".bmp")) {
            throw FileFormatError{"Wrong importing file format!"};
        }

        if (!exporting_file.ends_with(".bmp")) {
            throw FileFormatError{"Wrong exporting file format!"};
        }

        ++index;

        std::unique_ptr<ImageLoader> image_loader{new BMPImageLoader{}};
        Image image = image_loader->ImportImage(importing_file);

        while (index < argc) {
            std::unique_ptr<ImageProcessor> image_processor = parser.Parse();
            image_processor->ApplyFilter(image);
        }

        image_loader->ExportImage(exporting_file, image);
    } catch (const ParserError& error) {
        message << error.what() << '\n' << '\n';

        message << "-crop {width} {height} \t \t Crop image" << '\n';
        message << "-gs \t \t \t \t Convert image to grayscale" << '\n';
        message << "-neg \t \t \t \t Negative image's colors" << '\n';
        message << "-sharp \t \t \t \t Increase image's sharpness" << '\n';
        message << "-edge {threshold} \t \t Highlight image's borders" << '\n';
        message << "-blur {sigma} \t \t \t Blur image" << '\n';
        message << "-crystal {crystals count} \t Crystallize image" << std::endl;
    } catch (const LoaderError& error) {
        message << error.what() << std::endl;
    } catch (const FileFormatError& error) {
        message << error.what() << '\n';
        message << "BMP is supported." << std::endl;
    }

    return message;
}
