#include "ezinc.h"

static double cdtds, ppw = 0;

void ezIncInit(Grid *g){
  /* define the source parameters */
  printf("Enter the points per wavelength for harmonic source: ");
  scanf(" %lf", &ppw);
  cdtds = Cdtds;
  return;
}

double ezInc(double time) {
  /* calculate source function at given time */
  return cos(2 * M_PI * cdtds * time/ppw);
}
