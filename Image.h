#pragma once
typedef unsigned char byte;
typedef unsigned int int32;
typedef short int16;

struct Image {
    byte* pixels;
    int32 width;
    int32 height;
    int32 bytesPerPixel;

    ~Image() {
        free(pixels);
    }
};