#pragma once

#include <string>
#include "Image.h"

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

class ImageReader
{
public:  
	static Image* loadBMPfile(const std::string& fileName) {
       Image* image = new Image();

        FILE* imageFile = fopen(fileName.c_str(), "rb");
        int32 dataOffset;
        fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
        fread(&dataOffset, 4, 1, imageFile);
        fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
        fread(&image->width, 4, 1, imageFile);
        fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
        fread(&image->height, 4, 1, imageFile);
        int16 bitsPerPixel;
        fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
        fread(&bitsPerPixel, 2, 1, imageFile);
        image->bytesPerPixel = ((int32)bitsPerPixel) / 8;

        int paddedRowSize = (int)(4 * ceil((float)(image->width) / 4.0f)) * (image->bytesPerPixel);
        int unpaddedRowSize = (image->width) * (image->bytesPerPixel);
        int totalSize = unpaddedRowSize * (image->height);
        image->pixels = (byte*)malloc(totalSize);
        int i = 0;
        byte* currentRowPointer = image->pixels + ((image->height - 1) * unpaddedRowSize);
        for (i = 0; i < image->height; i++)
        {
            fseek(imageFile, dataOffset + (i * paddedRowSize), SEEK_SET);
            fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
            currentRowPointer -= unpaddedRowSize;
        }

       
        fclose(imageFile);
        return image;
	}
};