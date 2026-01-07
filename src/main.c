#include "cli.h"
#include "fractal.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Config Cfg;
  parseArguments(argc, argv, &Cfg);

  printf("Configuration: %dx%d, Output: %s\n", Cfg.Width, Cfg.Height,
         Cfg.OutputFilename);

  Image *Img = createImage(Cfg.Width, Cfg.Height);

  switch (Cfg.Type) {
  case FRACTAL_MANDELBROT:
    printf("Generating Mandelbrot Fractal...\n");
    drawMandelbrot(Img, Cfg.MaxIterations);
    break;
  case FRACTAL_JULIA:
    printf("Generating Julia Fractal...\n");
    drawJulia(Img, Cfg.MaxIterations);
    break;
  case FRACTAL_SIERPINSKI:
    printf("Generating Sierpinski Fractal...\n");
    drawSierpinski(Img, Cfg.MaxIterations);
    break;
  case FRACTAL_BURNING_SHIP:
    printf("Generating Burning Ship Fractal...\n");
    drawBurningShip(Img, Cfg.MaxIterations);
    break;
  default:
    // This part should be unreachable due to validation in parseArguments
    fprintf(stderr, "Error: Unhandled fractal type.\n");
    destroyImage(Img);
    return EXIT_FAILURE;
  }

  savePPM(Img, Cfg.OutputFilename);
  destroyImage(Img);

  return 0;
}
