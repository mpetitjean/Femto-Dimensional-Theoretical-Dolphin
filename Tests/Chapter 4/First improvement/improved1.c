/* Improved bare-bones 1D FDTD simulation. */

#include "fdtd1.h"
#include <math.h>

int main()
{
  Grid *g;                                   
  double imp0 = 377.0; 
  int mm;

  ALLOC_1D(g, 1, Grid)

  SizeX = 200;    // size of grid           
  MaxTime = 250;  // duration of simulation
  Cdtds = 1.0;    // Courant number (unused)

  ALLOC_1D(g->ez, SizeX, double);
  ALLOC_1D(g->hy, SizeX, double);

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) { 

    /* update magnetic field */
    for (mm = 0; mm < SizeX - 1; mm++)           
      Hy(mm) = Hy(mm) + (Ez(mm + 1) - Ez(mm)) / imp0;

    /* update electric field */
    for (mm = 1; mm < SizeX; mm++)
      Ez(mm) = Ez(mm) + (Hy(mm) - Hy(mm - 1)) * imp0;

    /* hardwire a source node */
    Ez(0) = exp(-(Time - 30.0) * (Time - 30.0) / 100.0);

    printf("%g\n", Ez(50));
  } /* end of time-stepping */

  return 0;
}
