#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

#define LOSS 0.1328         // Loss factor
#define PERM 43             // Relative permittivity

void gridInit(Grid *g) {
  double imp0 = 377.0;      // Z_0
  int mm, nn;

  /* terms for the lossy zone */
  double l, L, xLocation, yLocation, xCenter, yCenter, l2, L2;

  Type = tmZGrid;                          
  SizeX = 201;             // x size of domain
  SizeY = 201;              // y size of domain
  MaxTime = 102;           // duration of simulation
  Cdtds = 1.0 / sqrt(2.0); // Courant number

  /* Allocate memory for the arrays of coefficients */
  ALLOC_2D(g->hx,   SizeX, SizeY - 1, double);
  ALLOC_2D(g->chxh, SizeX, SizeY - 1, double);
  ALLOC_2D(g->chxe, SizeX, SizeY - 1, double);
  ALLOC_2D(g->hy,   SizeX - 1, SizeY, double);
  ALLOC_2D(g->chyh, SizeX - 1, SizeY, double);
  ALLOC_2D(g->chye, SizeX - 1, SizeY, double);
  ALLOC_2D(g->ez,   SizeX, SizeY, double);
  ALLOC_2D(g->ceze, SizeX, SizeY, double);
  ALLOC_2D(g->cezh, SizeX, SizeY, double);
 
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    /* loss-less zone */
    for (nn = 0; nn < SizeY; nn++) {
      Ceze(mm, nn) = 1.0;
      Cezh(mm, nn) = Cdtds * imp0;
      /* define lossy zone */
      if (mm >= 30 && mm <= 40 && nn <= 50)
      {
        Ceze(mm,nn) = (1.0 - LOSS) / (1.0 + LOSS);
        Cezh(mm,nn) = imp0 / PERM / (1.0 + LOSS) * Cdtds;
      }
    }
  /* set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) {
      Chxh(mm, nn) = 1.0;
      Chxe(mm, nn) = Cdtds / imp0;
    }
  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY; nn++) {
      Chyh(mm, nn) = 1.0;
      Chye(mm, nn) = Cdtds / imp0;
    }
  return;
}
