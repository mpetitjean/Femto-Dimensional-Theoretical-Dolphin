#include "fdtd-macro-tmz.h"

void updateH2d(Grid *g) {
  int mm, nn;

  /* update Hx for every node */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++)
    	Hx(mm, nn) = Chxh(mm, nn) * Hx(mm, nn) 
    	  - Chxe(mm, nn) * (Ez(mm, nn + 1) - Ez(mm, nn));

  /* update Hy for every node */
  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY; nn++)
    	Hy(mm, nn) = Chyh(mm, nn) * Hy(mm, nn) 
    	  + Chye(mm, nn) * (Ez(mm + 1, nn) - Ez(mm, nn));
  return;
}

void updateE2d(Grid *g) {
  int mm, nn;

  /* update Ez for every node */
  for (mm = 1; mm < SizeX - 1; mm++)
    for (nn = 1; nn < SizeY - 1; nn++)
    	Ez(mm, nn) = Ceze(mm, nn) * Ez(mm, nn) +
    	  Cezh(mm, nn) * ((Hy(mm, nn) - Hy(mm - 1, nn)) -
    		       (Hx(mm, nn) - Hx(mm, nn - 1)));
  return;
}
