#include "image.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Image *createImage(int Width, int Height) {
  assert(Width > 0 && Height > 0 && "Dimensions must be positive");

  Image *Img = (Image *)malloc(sizeof(Image));
  assert(Img != NULL && "Failed to allocate Image struct");

  Img->Width = Width;
  Img->Height = Height;
  Img->Data = (Pixel *)malloc(sizeof(Pixel) * Width * Height);
  assert(Img->Data != NULL && "Failed to allocate pixel buffer");

  return Img;
}

void destroyImage(Image *Img) {
  assert(Img != NULL);
  if (Img->Data) {
    free(Img->Data);
  }
  free(Img);
}

void setPixel(Image *Img, int X, int Y, Pixel Color) {
  assert(Img != NULL);
  assert(X >= 0 && X < Img->Width);
  assert(Y >= 0 && Y < Img->Height);
  Img->Data[(Y * Img->Width) + X] = Color;
}

void savePPM(const Image *Img, const char *Filename) {
  assert(Img != NULL && "Image cannot be NULL");
  assert(Filename != NULL && "Filename cannot be NULL");

  FILE *File = fopen(Filename, "wb");
  if (File == NULL) {
    fprintf(stderr, "Error: Could not open file '%s' for writing.\n", Filename);
    exit(EXIT_FAILURE);
  }

  fprintf(File, "P6\n%d %d\n255\n", Img->Width, Img->Height);
  size_t Written =
      fwrite(Img->Data, sizeof(Pixel), (long)Img->Width * Img->Height, File);
  assert(Written == (size_t)(Img->Width * Img->Height) &&
         "Incomplete file write");

  fclose(File);
  printf("Saved %s successfully.\n", Filename);
}
