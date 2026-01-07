#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

// Represents an RGB color pixel
typedef struct {
  uint8_t R;
  uint8_t G;
  uint8_t B;
} Pixel;

// Represents the image buffer
typedef struct {
  int Width;
  int Height;
  Pixel *Data;
} Image;

// Initialize an image with given dimensions
Image *createImage(int Width, int Height);

// Free image memory
void destroyImage(Image *Img);

// Save the image to a file in PPM format (P6)
void savePPM(const Image *Img, const char *Filename);

// Set a pixel at specific coordinates
void setPixel(Image *Img, int X, int Y, Pixel Color);

#endif // IMAGE_H
