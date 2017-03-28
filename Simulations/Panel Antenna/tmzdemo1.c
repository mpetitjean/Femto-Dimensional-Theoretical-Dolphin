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
  int esp = 3;
  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH2d(g);     // update magnetic field
    updateE2d(g);     // update electric field

    // source
    Ez(esp+10, SizeY/2) = ezInc(Time, 0.0);
    abc(g);

    // Reflector panel in x = 10
    for (int i = 0; i < SizeY; i++)
    {
      Ez(10,i) = 0.0;
    }
    snapshot2d(g);    // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
