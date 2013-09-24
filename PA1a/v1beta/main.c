#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nbody.h"
#include "display.h"

#define K 4

Vec2 forceTable[N][N];
int main(int argc, char *argv[]){
	double t0, t1, te;
	Body *bodies = (Body *) malloc (sizeof(Body ) * N);

	randTest (bodies, 0, N);
	struct BodyState bs0, bsK;

	bs0 = getState(bodies, N);
	wctime(&t0);
	nextPhase(bodies, dt, K, forceTable);
	wctime(&t1);
	bsK = getState(bodies, N);
	te = t1 - t0;

	printf("t0: %f\n", t0);
	printf("t1: %f\n", t1);
	printf("te: %f\n", te);
	printf("elapse - wc: %f\n", (K) * (N * N)/te * (1e-6));
	bodiesPrint(bodies, N-1, N);
	statePrint(&bs0);
	statePrint(&bsK);
	free(bodies);
	return 0;
}
