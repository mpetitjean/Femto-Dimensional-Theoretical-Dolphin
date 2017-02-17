/* Function initialize Grid structure. */

#include "fdtd3.h"

#define LOSS 0.02      
#define LOSS_LAYER 180  // node at which lossy layer starts
#define EPSR 9.0        

void gridInit3(Grid *g) {
  double imp0 = 377.0;
  int mm;

  SizeX = 200;   // size of domain         
  MaxTime = 450; // duration of simulation
  Cdtds = 1.0;   // Courant number         

  ALLOC_1D(g->ez,   SizeX, double);  
  ALLOC_1D(g->ceze, SizeX, double);
  ALLOC_1D(g->cezh, SizeX, double);
  ALLOC_1D(g->hy,   SizeX - 1, double);
  ALLOC_1D(g->chyh, SizeX - 1, double);
  ALLOC_1D(g->chye, SizeX - 1, double);
  
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    if (mm < 100) {
      Ceze(mm) = 1.0;
      Cezh(mm) = imp0;
    } else if (mm < LOSS_LAYER) {
      Ceze(mm) = 1.0;
      Cezh(mm) = imp0 / EPSR;
    } else {
      Ceze(mm) = (1.0 - LOSS) / (1.0 + LOSS);
      Cezh(mm) = imp0 / EPSR / (1.0 + LOSS);
    }

  /* set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX - 1; mm++)
    if (mm < LOSS_LAYER) {
      Chyh(mm) = 1.0;
      Chye(mm) = 1.0 / imp0;
    } else {
      Chyh(mm) = (1.0 - LOSS) / (1.0 + LOSS);
      Chye(mm) = 1.0 / imp0 / (1.0 + LOSS);
    }

  return;
}
