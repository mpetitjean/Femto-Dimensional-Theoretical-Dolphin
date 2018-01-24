#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h"
#include "fdtd-proto1.h"
#include "ezinc.h"

int main(){
  Grid *g;                                  // Create grid structure

  ALLOC_1D(g, 1, Grid);                     // allocate memory for Grid

  gridInit(g);                              // initialize all functions
  abcInit(g);
  ezIncInit(g);
  snapshotInit2d(g);     

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH2d(g);                           // update magnetic field
    updateE2d(g);                           // update electric field
    Ez(50, SizeY/2) = ezInc(Time);          // Source: impose Ez
    abc(g);                                 // absorbing boundary conditions
    snapshot2d(g);                          // save fields value
  }
  return 0;
}
