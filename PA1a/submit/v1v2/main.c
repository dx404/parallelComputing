#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nbody.h"
#include "display.h"

#define K 4

double bodyDiff(Body *a, Body *b, int size){
	Body *i = a, *j = b;
	double squareDiff = 0;
	double dvx, dvy;
	for (i = a; i != a + size; i++){
		dvx = a->velocity.x - b->velocity.x;
		dvy = a->velocity.y - b->velocity.y;
		squareDiff += dvx * dvx + dvy * dvy;
	}
	return squareDiff;
}

Vec2 forceTable[N][N];
int main(int argc, char *argv[]){
	double t0, t1, te;
	Body *bodies = (Body *) malloc (sizeof(Body ) * N);
	Body *bodies2 = (Body *) malloc (sizeof(Body ) * N);
	Body *bodies3 = (Body *) malloc (sizeof(Body ) * N);
	randInit (bodies, 0, N);
	bodyCopy(bodies2, bodies, 0, N);
//	randInit (bodies2, 0, N);

	struct BodyState bs0, bsK;

	bs0 = getState(bodies, N);
//	wctime(&t0);
	nextPhase(bodies, dt, K, forceTable);
	nextPhaseHalf(bodies2, dt, K, forceTable);
	double diff = bodyDiff(bodies, bodies2, N);
	printf("diff=%f\n", diff);
//	wctime(&t1);
	bsK = getState(bodies, N);
//	te = t1 - t0;

//	printf("t0: %f\n", t0);
//	printf("t1: %f\n", t1);
//	printf("te: %f\n", te);
//	printf("elapse - wc: %f\n", (K) * (N * N)/te * (1e-6));
//	printf("1.0, %d, %d, %f, %f\n", K, N, te, (K)*(N * N)/te * (1e-6));

	statePrint(&bs0);
	statePrint(&bsK);
	free(bodies);
	return 0;
}
