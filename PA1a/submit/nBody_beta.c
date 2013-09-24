#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define K 4
#define G 1
#define dt 0.001

struct Body{
	double Gmass;
	double px, py;
	double vx, vy;
	double ax, ay;
};

struct BodyState{
	double mvx, mvy;
	double energy;
};

struct BodyState getState(struct Body *body, int size){
	struct BodyState bs;
	bs.mvx = 0;
	bs.mvy = 0;
	bs.energy = 0;
	struct Body *i;
	for (i = body; i < body + size; i++){
		bs.mvx += i->Gmass * i->vx;
		bs.mvy += i->Gmass * i->vy;
		bs.energy += 0.5 * i->Gmass *(
					(i->vx) * (i->vx) +
					(i->vy) * (i->vy)
				);
	}
	return bs;
}

void statePrint(struct BodyState *s){
	printf("{mvx=%f, mvy=%f, energy=%f}\n", s->mvx, s->mvy, s->energy);
}

void wctime(double *t) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	*t = tv.tv_sec + (1E-6) * tv.tv_usec;
}

double fastInvSqrt(double number) {
	double x2 = number * 0.5;
	double y = number;
	uint64_t i = *(uint64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *) &i;
	y = y * (1.5 - (x2 * y * y));
	return y;
}
double fastInvSqrtCube(double number) {
	double x2 = number * 0.5;
	double y = number;
	uint64_t i = *(uint64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *) &i;
	y = y * (1.5 - (x2 * y * y));
	return y;
}

void quickNormalize(double *dx, double *dy){
	double d2  = *dx * *dx + *dy * *dy;
	double y = d2;
	uint64_t i = 0x5fe6eb50c7b537a9 - ((*(uint64_t *) &d2) >> 1);
	y = *(double *) &i;
	y *=   (1.5 - (0.5 * d2 * y * y)) ;
//	y *=   (1.5 - (0.5 * d2 * y * y)) ;
//	y *=   (1.5 - (0.5 * d2 * y * y)) ;
	y *= y*y;
	*dx *=  y;
	*dy *=  y;
}

void reNormalize(double *dx, double *dy){
	double d2  = *dx * *dx + *dy * *dy;
	double d3 = d2 * sqrt(d2);
	*dx /=  d3;
	*dy /=  d3;
}

void randTest(struct Body *bodies, int start, int end){
	int i;
	for (i = start; i < end; i++){
		bodies[i].Gmass = G * 1;
		bodies[i].px = 0.1 * i;
		bodies[i].py = 0.1 * i;
		bodies[i].vx = 1;
		bodies[i].vy = 1;
		bodies[i].ax = 0;
		bodies[i].ay = 0;
	}
}

void randInit(struct Body *body, int start, int end){
	srand (time(NULL));
	struct Body *i;
	for (i = body + start; i < body + end; i++){
		i->Gmass = (float)rand()/(float)RAND_MAX;
		i->px = (float)rand()/(float)RAND_MAX;
		i->py = (float)rand()/(float)RAND_MAX;
		i->vx = 1.5 * (float)rand()/(float)RAND_MAX;
		i->vy = 1.5 * (float)rand()/(float)RAND_MAX;
	}
}

void bodiesPrint(struct Body *bodies, int start, int end){
	int i;
	printf("{");
	for (i = start; i < end; i++){
		printf("p={%f, %f}\n", bodies[i].px, bodies[i].py);
		printf("v={%f, %f}\n", bodies[i].vx, bodies[i].vy);
		printf("a={%f, %f}\n", bodies[i].ax, bodies[i].ay);
		if (i == end - 1)
			break;
		else
			printf(", ");

	}
	printf("}, \n");
}

void nextPhase(struct Body *body, int num, int steps, double *clock_record){
	wctime(clock_record++);
	int t;
	struct Body *i, *j;

	double ax, ay;
	double dx, dy;
	for (t = 0; t < steps; t++){
		for (i = body; i != body + num; i++){
			ax = i->ax;
			ay = i->ay;
			for (j = i + 1; j != body + num; j++){
				dx = i->px - j->px;
				dy = i->py - j->py;
				quickNormalize(&dx, &dy);
//				reNormalize(&dx, &dy);

				ax -= j->Gmass * dx;
				ay -= j->Gmass * dy;

				j->ax += i->Gmass * dx;
				j->ay += i->Gmass * dy;

			}
			i->px += dt * i->vx;
			i->py += dt * i->vy;

			i->vx += dt * ax;
			i->vy += dt * ay;

			i->ax = 0;
			i->ay = 0;
		}
		wctime(clock_record++);
	}
}


int main(int argc, char *argv[]){
	if (argc < 2){
		printf("%s\n", "Usage: Please input the number of bodies");
		return 1;
	}
	int N = atoi(argv[1]);
	double te;

	struct Body *body = (struct Body *) malloc (sizeof(struct Body ) * N);
	double t[K+1];
//	randTest (body, 0, N);
	randInit (body, 0, N);

	struct BodyState bs0, bsK;

//	bs0 = getState(body, N);
	nextPhase(body, N, K, t);
//	bsK = getState(body, N);

	te = t[K] - t[0];
//	printf("t0: %f\n", t[0]);
//	printf("tK: %f\n", t[K]);
//	printf("te: %f\n", te);
//	printf("te/K: %f\n", te/K);
//	printf("elapse - k n^2/t_e: %f\n", (K) * (N*N)/te*(1e-6));
//	printf("-----%f\n", fastInvSqrt(3.1415926));
//	printf("-----%f\n", 1/sqrt(3.1415926));

	printf("3.0, %d, %d, %f, %f\n", K, N, te, (K)*(N * N)/te * (1e-6));

//	bodiesPrint(body, 0, N);
//	statePrint(&bs0);
//	statePrint(&bsK);

//	bodiesPrint(body, 0, N);
	free(body);
	return 0;
}
