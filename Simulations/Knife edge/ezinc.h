#ifndef _EZINC_H
#define _EZINC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"

void ezIncInit(Grid *g); 
double ezInc(double time, double location);

#endif
