#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define K 4
#define G 10
#define dt 0.001
#define N 5000


struct Body{
	double Gmass;
	double px, py;
	double vx, vy;
	double ax, ay;
}b;

void wctime(double *t) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	*t = tv.tv_sec + (1E-6) * tv.tv_usec;
}

double fastInvSqrtCube(double number) {
	double x2 = number * 0.5;
	double y = number;
	uint64_t i = *(uint64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *) &i;
	y = y * (1.5 - (x2 * y * y));
	return y / number;
}

void overNormalize(double *dx, double *dy){
	double d2  = *dx * *dx + *dy * *dy;
	double y = d2;
	uint64_t i = 0x5fe6eb50c7b537a9 - ((*(uint64_t *) &d2) >> 1);
	y = *(double *) &i;
	y *=   (1.5 - (0.5 * d2 * y * y)) ;
	y *= y*y;
	*dx *=  y;
	*dy *=  y;
}

void randTest(struct Body *bodies, int start, int end){
	int i;
	for (i = start; i < end; i++){
		bodies[i].Gmass = K * 1;
		bodies[i].px = 0.1 * i;
		bodies[i].py = 0.1 * i;
		bodies[i].vx = 1;
		bodies[i].vy = 1;
		bodies[i].ax = 0;
		bodies[i].ay = 0;
	}
}


int main(int argc, char *argv[]){
	double t0, t1, te;

	struct Body *body = (struct Body *) malloc (sizeof(struct Body ) * N);

	randTest (body, 0, N);

	struct Body *i, *j;
	double dx, dy, rdx, rdy, d, d2, d3, ax, ay, ipx, ipy, iGmass, d3inv;

	wctime(&t0);
	for (i = body; i != body + N; i++){
		ax = i->ax;
		ay = i->ay;
		for (j = i + 1; j != body + N; j++){
			dx = i->px - j->px;
			dy = i->py - j->py;
			d2 = dx * dx + dy * dy;
//			d3inv = fastInvSqrtCube(d2);
//			dx *= d3inv;
//			dy *= d3inv;
			overNormalize(&dx, &dy);


			ax -= j->Gmass * dx;
			ay -= j->Gmass * dy;

			j->ax += i->Gmass * dx;
			j->ay += i->Gmass * dy;

		}
		i->px += dt * i->vx;
		i->py += dt * i->vy;

		i->vx += dt * ax;
		i->vy += dt * ay;
	}
	wctime(&t1);
	te = t1 - t0;

	printf("t0: %f\n", t0);
	printf("t1: %f\n", t1);
	printf("te: %f\n", te);
	printf("elapse - k n^2/t_e: %f\n", (K) * (N*N)/te	*(1e-6));

	free(body);
	return 0;
}
