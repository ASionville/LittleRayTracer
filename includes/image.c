#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "color.h"
#include "image.h"

// Create a new image
Image newImage(int width, int height) {
    Image img;
    img.width = width;
    img.height = height;
    img.pixels = malloc(width * sizeof(Color*));
    for (int i = 0; i < width; i++) {
        img.pixels[i] = malloc(height * sizeof(Color));
    }
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            img.pixels[i][j] = newColor(0, 0, 0);
        }
    }
    return img;
}

// Save BMP image to file
void saveImage(Image image, char* filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }

    // BMP header
    fprintf(f, "P3\n%d %d\n255\n", image.width, image.height);

    // BMP image data
    for (int j = image.height-1; j>=0; j--)
    {
        for (int i = 0; i < image.width; i++)
        {
            // Convert pixel color to 0-255 range, and write to file
            Color c = image.pixels[i][j];
            int r = (int)(255.999 * c.r);
            int g = (int)(255.999 * c.g);
            int b = (int)(255.999 * c.b);
            fprintf(f, "%d %d %d\n", r, g, b);
        }
    }
}

// Set a pixel in the image
void setPixel(Image image, int x, int y, Color color) {
    image.pixels[x][y] = color;
}