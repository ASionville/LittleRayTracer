#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"

typedef struct {
    int width;
    int height;
    Color **pixels;
} Image;

Image newImage(int width, int height);
void saveImage(Image image, char *filename);
void setPixel(Image image, int x, int y, Color color);

#endif // !IMAGE_H