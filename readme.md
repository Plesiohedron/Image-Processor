# Image Processor

A program that applies various filters to BMP images, similar to filters in popular image editors. \
You can view examples of output images in the `examples` folder.

## Build

Create a directory with the build and launch CMake in it. \
Create executable files:
```
make image_processor
make test_image_processor
```

It is recommended to extract the executable files from the build directory for running `test_image_processor` correctly.

## Command line argument format

`{program name} {path to input file} {path to output file} [-{filter name 1} [filter parameter 1] [filter parameter 2] ...] [-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...`

### Example

`./image_processor input/lenna.bmp output/lenna_crop_gs_blur.bmp -crop 800 600 -gs -blur 0.5`

`test_image_processor` runs without parameters.

## Filters

#### Crop   `-crop [width] [height]`

Crops the image to the specified `width` and `height` (natural numbers). The upper left part of the image is used. \
If the requested width or height exceeds the dimensions of the original image, the available part of the image is displayed.

#### Grayscale `-gs`

Converts an image to grayscale.

#### Negative `-neg`

Converts an image to a negative.

#### Sharpening `-sharp`

Increases the sharpness of the image.

#### Edge Detection `-edge [threshold]`

Highlights the borders of the image. \
Pixels with a value higher than `threshold` (float) are colored white, and the rest are colored black.

#### Gaussian Blur `-blur [sigma]`

Gaussian blur by `sigma` (float) parameter.

#### Crystallize `-crystal [number of crystals]`

"Crystallizes" the image according to a given `number of crystals` (natural number).
