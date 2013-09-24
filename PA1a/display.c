#include <stdio.h>
#include <sys/time.h>
#include "nbody.h"

void bodiesPrint(Body bodies[], int start, int end){
	int i;
	printf("{");
	for (i = start; i < end; i++){
		printf("{%f, %f}", bodies[i].position.x, bodies[i].position.y);
		if (i == end - 1)
			break;
		else
			printf(", ");

	}
	printf("}, \n");
}

void wctime(double *t) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	*t = tv.tv_sec + (1E-6) * tv.tv_usec;
}


