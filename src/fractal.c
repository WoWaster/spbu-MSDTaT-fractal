#include "fractal.h"
#include "image.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

// Internal helper to map iteration count to a color
static Pixel mapColor(int Iterations, int MaxIterations) {
  Pixel P;
  if (Iterations == MaxIterations) {
    P.R = 0;
    P.G = 0;
    P.B = 0;
    return P;
  }

  P.R = (Iterations * 7) % 255;
  P.G = (Iterations * 13) % 255;
  P.B = (Iterations * 17) % 255;
  return P;
}

void drawMandelbrot(Image *Img, int MaxIterations) {
  assert(Img != NULL);

  double MinRe = -2.0;
  double MaxRe = 1.0;
  double MinIm = -1.2;
  double MaxIm = 1.2;
  double ReFactor = (MaxRe - MinRe) / (Img->Width - 1);
  double ImFactor = (MaxIm - MinIm) / (Img->Height - 1);

  for (int Y = 0; Y < Img->Height; ++Y) {
    double CIm = MaxIm - (Y * ImFactor);
    for (int X = 0; X < Img->Width; ++X) {
      double CRe = MinRe + (X * ReFactor);
      double ZRe = CRe;
      double ZIm = CIm;
      int N;

      for (N = 0; N < MaxIterations; ++N) {
        double ZRe2 = ZRe * ZRe;
        double ZIm2 = ZIm * ZIm;
        if (ZRe2 + ZIm2 > 4) {
          break;
        }
        ZIm = (2 * ZRe * ZIm) + CIm;
        ZRe = ZRe2 - ZIm2 + CRe;
      }
      setPixel(Img, X, Y, mapColor(N, MaxIterations));
    }
  }
}

void drawJulia(Image *Img, int MaxIterations) {
  assert(Img != NULL);

  double CRe = 0.285;
  double CIm = 0.01;
  double Zoom = 1.0;

  for (int Y = 0; Y < Img->Height; ++Y) {
    for (int X = 0; X < Img->Width; ++X) {
      double ZRe = 1.5 * (X - Img->Width / 2.0) / (0.5 * Zoom * Img->Width);
      double ZIm = (Y - Img->Height / 2.0) / (0.5 * Zoom * Img->Height);

      int N;
      for (N = 0; N < MaxIterations; ++N) {
        double ZRe2 = ZRe * ZRe;
        double ZIm2 = ZIm * ZIm;
        if (ZRe2 + ZIm2 > 4) {
          break;
        }
        ZIm = (2 * ZRe * ZIm) + CIm;
        ZRe = ZRe2 - ZIm2 + CRe;
      }
      setPixel(Img, X, Y, mapColor(N, MaxIterations));
    }
  }
}

void drawSierpinski(Image *Img, int MaxIterations) {
  assert(Img != NULL);

  Pixel WhitePixel = {.R = 255, .G = 255, .B = 255};
  for (int X = 0; X < Img->Width; ++X) {
    for (int Y = 0; Y < Img->Height; ++Y) {
      setPixel(Img, X, Y, WhitePixel);
    }
  }

  double Vx[] = {Img->Width / 2.0, 0.0, Img->Height - 1.0};
  double Vy[] = {0.0, Img->Height - 1.0, Img->Height - 1.0};

  double X = rand() % Img->Width;
  double Y = rand() % Img->Height;

  Pixel BlackPixel = {.R = 0, .G = 0, .B = 0};

  for (int I = 0; I < MaxIterations; ++I) {
    int R = rand() % 3;

    X = (X + Vx[R]) / 2.0;
    Y = (Y + Vy[R]) / 2.0;

    int Px = (int)X;
    int Py = (int)Y;

    if (Px >= 0 && Px < Img->Width && Py >= 0 && Py < Img->Height) {
      setPixel(Img, Px, Py, BlackPixel);
    }
  }
}

void drawBurningShip(Image *Img, int MaxIterations) {
  assert(Img != NULL);

  double MinRe = -2.5;
  double MaxRe = 2.0;
  double MinIm = -2.0;
  double MaxIm = 1.0;
  double ReFactor = (MaxRe - MinRe) / (Img->Width - 1);
  double ImFactor = (MaxIm - MinIm) / (Img->Height - 1);

  for (int Y = 0; Y < Img->Height; ++Y) {
    double CIm = MaxIm - (Y * ImFactor);
    for (int X = 0; X < Img->Width; ++X) {
      double CRe = MinRe + (X * ReFactor);
      double ZRe = CRe;
      double ZIm = CIm;
      int N = 0;

      for (N = 0; N < MaxIterations; ++N) {
        double ZRe2 = ZRe * ZRe;
        double ZIm2 = ZIm * ZIm;
        if (ZRe2 + ZIm2 > 4) {
          break;
        }
        ZIm = fabs(2 * ZRe * ZIm) + CIm;
        ZRe = ZRe2 - ZIm2 + CRe;
      }
      setPixel(Img, X, Y, mapColor(N, MaxIterations));
    }
  }
}
