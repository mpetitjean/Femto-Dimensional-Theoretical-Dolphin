/* TMz simulation with Ricker source at center of grid. */

#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid); // allocate memory for Grid

  gridInit(g);        // initialize the grid
  abcInit(g);
  ezIncInit(g);
  snapshotInit2d(g);  // initialize snapshots
  int shift = 3;
  double dphi = 0.3273;
  //double dphi = 0.9425;
  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH2d(g);     // update magnetic field
    updateE2d(g);     // update electric field

    // sources
    // For a broadside array (chap6 p5), delta = 0
    Ez(10, SizeY/2-shift/2) = ezInc(Time, 0.0, dphi);
    Ez(10, SizeY/2+shift/2) = ezInc(Time, 0.0, 2*dphi); 
    Ez(10, SizeY/2+3*shift/2) = ezInc(Time, 0.0, 3*dphi); 
    Ez(10, SizeY/2-3*shift/2) = ezInc(Time, 0.0, 0.0);  
    abc(g);
    snapshot2d(g);    // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
