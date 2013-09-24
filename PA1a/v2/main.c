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
	uint64_t i;
	double x2, y;
	x2 = number * 0.5;
	y = number;
	i = *(uint64_t *) &y;
	i = 0x5fe6eb50c7b537a9 - (i >> 1);
	y = *(double *) &i;
	y = y * (1.5 - (x2 * y * y));
	return y / number;
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

void nextPhase_001(struct Body *body, int start, int end){
	int i, j;
	double dx, dy, d, d2, d3;
	for (i = start; i < end; i++)
		for (j = i + 1; j < end; j++){
			dx = body[j].px - body[i].px;
			dy = body[j].py - body[i].py;
			d2 = dx * dx + dy * dy;
			d3 = d2 * sqrt(d2);

			dx /= d3;
			dy /= d3;
			body[i].ax += body[j].Gmass * dx;
			body[i].ay += body[j].Gmass * dy;

			body[j].ax -= body[i].Gmass * dx;
			body[j].ay -= body[i].Gmass * dy;

			body[i].px += dt * body[i].vx;
			body[i].py += dt * body[i].vy;

			body[i].vx += dt * body[i].ax;
			body[i].vy += dt * body[i].ay;

		}

}

void nextPhase_002(struct Body *body, int start, int end){
	struct Body *i, *j;
	double dx, dy, d, d2, d3;
	struct Body *body_start = &body[start];
	struct Body *body_end = &body[end];

	for (i = body_start; i != body_end; i++)
		for (j = i + 1; j != body_end; j++){
			dx = j->px - i->px;
			dy = j->py - i->py;
			d2 = dx * dx + dy * dy;
			d3 = d2 * sqrt(d2);

			dx /= d3;
			dy /= d3;
			i->ax += j->Gmass * dx;
			i->ay += j->Gmass * dy;

			j->ax -= i->Gmass * dx;
			j->ay -= i->Gmass * dy;

			i->px += dt * i->vx;
			i->py += dt * i->vy;

			i->vx += dt * i->ax;
			i->vy += dt * i->ay;

		}

}

void nextPhase_003(struct Body *body, int start, int end){
	struct Body *i, *j;
	double dx, dy, d, d2, d3;
	struct Body *body_start = &body[start];
	struct Body *body_end = &body[end];

	for (i = body_start; i != body_end; i++)
		for (j = i + 1; j != body_end; j++){
			dx = j->px - i->px;
			dy = j->py - i->py;
			d2 = dx * dx + dy * dy;
			//			d3 = d2 * sqrt(d2);

			d3 = fastInvSqrtCube(d2);

			dx *= d3;
			dy *= d3;
			i->ax += j->Gmass * dx;
			i->ay += j->Gmass * dy;

			j->ax -= i->Gmass * dx;
			j->ay -= i->Gmass * dy;

			i->px += dt * i->vx;
			i->py += dt * i->vy;

			i->vx += dt * i->ax;
			i->vy += dt * i->ay;

		}


}

void nextPhase_004(struct Body *body, int start, int end){
	struct Body *i, *j;
	double dx, dy, d, d2, d3, ax, ay, ipx, ipy, iGmass;

	for (i = body + start; i != body + end; i++){
		ax = i->ax;
		ay = i->ay;
		for (j = i + 1; j != body + end; j++){
			dx = i->px - j->px;
			dy = i->py - j->py;
			d2 = dx * dx + dy * dy;
			d3 = d2 * sqrt(d2);

			dx /= d3;
			dy /= d3;

			ax -= j->Gmass * dx;
			ay -= j->Gmass * dy;

			j->ax += iGmass * dx;
			j->ay += iGmass * dy;

		}
		i->px += dt * i->vx;
		i->py += dt * i->vy;

		i->vx += dt * ax;
		i->vy += dt * ay;
	}

}


int main(int argc, char *argv[]){
	double t0, t1, te;

	struct Body *bodies = (struct Body *) malloc (sizeof(struct Body ) * N);
	struct Body *body = bodies;
	randTest (bodies, 0, N);

	wctime(&t0);
	struct Body *i, *j;
	double dx, dy, d, d2, d3, ax, ay, ipx, ipy;

	for (i = body; i != body + N; i++){
		ax = i->ax;
		ay = i->ay;
		for (j = i + 1; j != body + N; j++){
			dx = i->px - j->px;
			dy = i->py - j->py;
			d2 = dx * dx + dy * dy;
			d3 = d2 * sqrt(d2);

			dx /= d3;
			dy /= d3;

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
	printf("elapse - wc: %f\n", (K) * (N*N)/te	*(1e-9));

	free(bodies);
	return 0;
}
