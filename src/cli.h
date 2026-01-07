#ifndef CLI_H
#define CLI_H

#include "fractal.h"

// Configuration structure holding runtime parameters
typedef struct {
  int Width;
  int Height;
  char *OutputFilename;
  FractalType Type;
  int MaxIterations;
} Config;

// Parse command line arguments into Config struct
void parseArguments(int Argc, char *Argv[], Config *Cfg);

#endif // CLI_H
