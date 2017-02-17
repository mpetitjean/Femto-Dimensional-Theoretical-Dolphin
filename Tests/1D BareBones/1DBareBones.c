/*
 * 1DBareBones.c
 *
 *  Created on: Feb 16, 2017
 *      Author: mathieu
 */
/* Bare-bones 1D FDTD simulation with a hard source. */
#include <stdio.h>
#include <math.h>

#define SIZE 200

int main(){

	/* declaration for saving snapshots */
	char basename[80] = "sim", filename[100];
	int frame = 0;
	FILE *snapshot;

	double ez[SIZE] = {0.}, hy[SIZE] = {0.}, imp0 = 377.0;
	/* instanciates int qTime, sets maxTime at 250, instanciates mm*/
	int qTime, maxTime = 250, mm;

	/* do time stepping */
	for (qTime = 0; qTime < maxTime; qTime++) {

		/* spatial stepping for B and H */

		/* update magnetic field */
		for (mm = 0; mm < SIZE - 1; mm++)
			hy[mm] = hy[mm] + (ez[mm + 1] - ez[mm]) / imp0;

		/* update electric field */
		for (mm = 1; mm < SIZE; mm++)
			ez[mm] = ez[mm] + (hy[mm] - hy[mm - 1]) * imp0;

		/* hardwire a source node */
		ez[0] = exp(-(qTime - 30.) * (qTime - 30.) / 100.);
		

		/* write snapshot if time-step is a multiple of 10 */
		if (qTime % 10 == 0) {
			/* construct complete file name and increment frame counter */
			sprintf(filename, "%s.%d", basename, frame++);

			/* open file */
			snapshot = fopen(filename, "w");

			/* write data to file */
			for (mm = 0; mm < SIZE; mm++)
			fprintf(snapshot, "%g\n", ez[mm]);

			/* close file */
			fclose(snapshot);
		}

	} /* end of time-stepping */

	return 0;
}
