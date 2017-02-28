#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include <math.h>

#define LOSS 0.1          // Loss factor
#define PERM 4.5          // Relative permittivity

void gridInit(Grid *g) {
  double imp0 = 377.0;
  int mm, nn;

  Type = tmZGrid;                          /*@ \label{gridtmzA} @*/
  SizeX = 101;             // x size of domain
  SizeY = 81;              // y size of domain
  MaxTime = 230;           // duration of simulation
  Cdtds = 1.0 / sqrt(2.0); // Courant number

  ALLOC_2D(g->hx,   SizeX, SizeY - 1, double);  /*@ \label{gridtmzB} @*/
  ALLOC_2D(g->chxh, SizeX, SizeY - 1, double);
  ALLOC_2D(g->chxe, SizeX, SizeY - 1, double);
  ALLOC_2D(g->hy,   SizeX - 1, SizeY, double);
  ALLOC_2D(g->chyh, SizeX - 1, SizeY, double);
  ALLOC_2D(g->chye, SizeX - 1, SizeY, double);
  ALLOC_2D(g->ez,   SizeX, SizeY, double);
  ALLOC_2D(g->ceze, SizeX, SizeY, double);
  ALLOC_2D(g->cezh, SizeX, SizeY, double);    /*@ \label{gridtmzC} @*/
 
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY; nn++) {
      Ceze(mm, nn) = 1.0;
      Cezh(mm, nn) = Cdtds * imp0;

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

      // if (mm >= 30 && mm <= 40 && nn >= 30)
      // {
      //   Chxh(mm,nn) = (1.0 - LOSS) / (1.0 + LOSS);
      //   Chxh(mm,nn) = Cdtds / PERM / (1.0 + LOSS); * imp0;
      // }
    }

  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY; nn++) {
      Chyh(mm, nn) = 1.0;
      Chye(mm, nn) = Cdtds / imp0;
    }

  return;
}
