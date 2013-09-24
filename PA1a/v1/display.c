#include <stdio.h>
#include <sys/time.h>
#include "nbody.h"
#include "display.h"

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

struct BodyState getState(Body *body, int size){
	struct BodyState bs;
	bs.mvx = 0;
	bs.mvy = 0;
	bs.energy = 0;
	Body *i;
	for (i = body; i < body + size; i++){
		bs.mvx += i->mass * i->velocity.x;
		bs.mvy += i->mass * i->velocity.y;
		bs.energy += 0.5 * i->mass *(
					(i->velocity.x) * (i->velocity.x) +
					(i->velocity.y) * (i->velocity.y)
				);
	}
	return bs;
}

void statePrint(struct BodyState *s){
	printf("{mvx=%f, mvy=%f, energy=%f}\n", s->mvx, s->mvy, s->energy);
}


