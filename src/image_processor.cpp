#include "ImageLoaders/BMPLoader.h"
#include "Parser/Parser.h"
#include "Exceptions/Exceptions.h"

int main(const int argc, const char* argv[]) {

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
        std::cerr << error.what() << '\n' << '\n';

        std::cerr << "-crop {width} {height} \t \t Crop image" << '\n';
        std::cerr << "-gs \t \t \t \t Convert image to grayscale" << '\n';
        std::cerr << "-neg \t \t \t \t Negative image's colors" << '\n';
        std::cerr << "-sharp \t \t \t \t Increase image's sharpness" << '\n';
        std::cerr << "-edge {threshold} \t \t Highlight image's borders" << '\n';
        std::cerr << "-blur {sigma} \t \t \t Blur image" << '\n';
        std::cerr << "-crystal {crystals count} \t Crystallize image" << std::endl;
    } catch (const LoaderError& error) {
        std::cerr << error.what() << std::endl;
    } catch (const FileFormatError& error) {
        std::cerr << error.what() << '\n';
        std::cerr << "BMP is supported." << std::endl;
    }
}
