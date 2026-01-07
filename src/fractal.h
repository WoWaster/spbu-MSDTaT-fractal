#ifndef FRACTAL_H
#define FRACTAL_H

#include "image.h"

// Available fractal types
typedef enum {
  FRACTAL_UNKNOWN = 0,
  FRACTAL_MANDELBROT,
  FRACTAL_JULIA,
  FRACTAL_SIERPINSKI,
  FRACTAL_BURNING_SHIP
} FractalType;

// Draw the Mandelbrot Set onto the image
void drawMandelbrot(Image *Img, int MaxIterations);

// Draw the Julia Set onto the image
void drawJulia(Image *Img, int MaxIterations);

// Draw Sierpinski triangle onto the image
void drawSierpinski(Image *Img, int MaxIterations);

// Draw Burning Ship fractal onto the image
void drawBurningShip(Image *Img, int MaxIterations);

#endif // FRACTAL_H
