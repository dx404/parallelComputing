#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nbody.h"

int main(int argc, char *argv[]){
	int K = 9;
	int i, j;
	double t0, t1;
	double t_elapsed;
	double tc_0, tc_1, tc_e;

	struct timeval tv;


	Body bodies[N], bodies2[N];
	Vec2 forceTable[N][N];

	randInit (bodies, 0, N);
//	bodyCopy(bodies2, bodies, 0, N);

	printf("data = {");

	gettimeofday(&tv, NULL);
	t0 = tv.tv_sec + (double) tv.tv_usec / 1000000;

	tc_0 = clock();
	nextPhase(bodies, dt, K, forceTable);
	tc_1 = clock();

	gettimeofday(&tv, NULL);
	t1 = tv.tv_sec + (double) tv.tv_usec / 1000000;
	tc_e = (tc_1 - tc_0) / (double) CLOCKS_PER_SEC;
	t_elapsed = t1 - t0;

	printf("};===\n");
	printf("elapse: %f\n", t0);
	printf("elapse: %f\n", t1);
	printf("elapse: %f\n", t1 - t0);
	printf("elapse - wc: %f\n", (K) * (N*N)/t_elapsed	*(1e-9));
	printf("elapse - cl: %f\n", (K) * (N*N)/tc_e	*(1e-9));


	return 0;
}
