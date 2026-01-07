#include "cli.h"
#include "fractal.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printHelp(const char *ProgramName) {
  printf(
      "Usage: %s --type [mandelbrot|julia|sierpinski|burningShip] [options]\n",
      ProgramName);
  printf("Options:\n");
  printf("  --type [mandelbrot|julia|sierpinski|burningShip]  Select fractal "
         "type (REQUIRED)\n");
  printf("  --width [int]                                     Set image width "
         "(default: 800)\n");
  printf("  --height [int]                                    Set image height "
         "(default: 600)\n");
  printf("  --output [filename]                               Set output "
         "filename (default: output.ppm)\n");
  printf("  --help                                            Show this help "
         "message\n");
}

void parseArguments( // NOLINT(readability-function-cognitive-complexity)
    int Argc, char *Argv[], Config *Cfg) {
  assert(Cfg != NULL);

  // Set defaults
  Cfg->Width = 800;
  Cfg->Height = 600;
  Cfg->OutputFilename = "output.ppm";
  // Initialize as unknown to enforce user selection
  Cfg->Type = FRACTAL_UNKNOWN;
  Cfg->MaxIterations = 1000;

  for (int I = 1; I < Argc; ++I) {
    if (strcmp(Argv[I], "--help") == 0) {
      printHelp(Argv[0]);
      exit(EXIT_SUCCESS);
    } else if (strcmp(Argv[I], "--type") == 0) {
      if (I + 1 < Argc) {
        if (strcmp(Argv[I + 1], "julia") == 0) {
          Cfg->Type = FRACTAL_JULIA;
        } else if (strcmp(Argv[I + 1], "mandelbrot") == 0) {
          Cfg->Type = FRACTAL_MANDELBROT;
        } else if (strcmp(Argv[I + 1], "sierpinski") == 0) {
          Cfg->Type = FRACTAL_SIERPINSKI;
        } else if (strcmp(Argv[I + 1], "burningShip") == 0) {
          Cfg->Type = FRACTAL_BURNING_SHIP;
        } else {
          fprintf(stderr, "Error: Unknown type '%s'.\n", Argv[I + 1]);
          printHelp(Argv[0]);
          exit(EXIT_FAILURE);
        }
        I++;
      } else {
        fprintf(stderr, "Error: Missing argument for --type\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(Argv[I], "--width") == 0) {
      if (I + 1 < Argc) {
        Cfg->Width = atoi(Argv[++I]);
      } else {
        fprintf(stderr, "Error: Missing argument for --width\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(Argv[I], "--height") == 0) {
      if (I + 1 < Argc) {
        Cfg->Height = atoi(Argv[++I]);
      } else {
        fprintf(stderr, "Error: Missing argument for --height\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(Argv[I], "--output") == 0) {
      if (I + 1 < Argc) {
        Cfg->OutputFilename = Argv[++I];
      } else {
        fprintf(stderr, "Error: Missing argument for --output\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(Argv[I], "--maxIterations") == 0) {
      if (I + 1 < Argc) {
        Cfg->MaxIterations = atoi(Argv[++I]);
      } else {
        fprintf(stderr, "Error: Missing argument for --maxIterations\n");
        exit(EXIT_FAILURE);
      }
    } else {
      fprintf(stderr, "Error: Unknown option '%s'.\n", Argv[I]);
      printHelp(Argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  // Validate that a type was selected
  if (Cfg->Type == FRACTAL_UNKNOWN) {
    fprintf(stderr, "Error: You must specify a fractal type using --type.\n");
    printHelp(Argv[0]);
    exit(EXIT_FAILURE);
  }

  assert(Cfg->Width > 0 && "Width must be positive");
  assert(Cfg->Height > 0 && "Height must be positive");
}
