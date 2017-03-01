#include "ezinc.h"

static double cdtds, ppw = 0;

/* initialize source-function variables */
void ezIncInit(Grid *g){

  printf("Enter the points per wavelength for harmonic source: ");
  scanf(" %lf", &ppw);
  cdtds = Cdtds;   /*@ \label{ezinc2DA} @*/
  return;
}

/* calculate source function at given time and location */
double ezInc(double time, double location) {
  double arg;

  if (ppw <= 0) {
    fprintf(stderr,
       "ezInc: ezIncInit() must be called before ezInc.\n"
       "       Points per wavelength must be positive.\n");
    exit(-1);
  }

  return cos(2 * M_PI * (cdtds * time - location)/ppw);
}
