#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define K 4
#define G 10
#define dt 0.001


struct Body{
	double Gmass;
	double px, py;
	double vx, vy;
};

struct Vec2{
	double x, y;
};

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
	}
}


void nextPhase_005(struct Body *body, int start, int end){
	struct Body *i, *j;
	double dx, dy, d, d2, d3, ax, ay, ipx, ipy, iGmass;

	struct Vec2 *ac = (struct Vec2 *) malloc ((end-start) * sizeof(struct Vec2));
//	struct Vec2 *ac = (struct Vec2*) malloc (end-start, sizeof(struct Vec2));
	struct Vec2 *ia, *ja;
	for (i = body + start, ia = ac; i != body + end; i++, ia++){
		ax = ia->x;
		ay = ia->y;
		for (j = i + 1, ja = ia + 1; j != body + end; j++, ja++){
			dx = i->px - j->px;
			dy = i->py - j->py;
			d2 = dx * dx + dy * dy;
			d3 = d2 * sqrt(d2);

			dx /= d3;
			dy /= d3;

			ax -= j->Gmass * dx;
			ay -= j->Gmass * dy;

			ja->x += i->Gmass * dx;
			ja->y += i->Gmass * dy;

		}
		i->px += dt * i->vx;
		i->py += dt * i->vy;

		i->vx += dt * ax;
		i->vy += dt * ay;
	}
	free(ac);
}


int main(int argc, char *argv[]){
	if (argc < 2){
		printf("%s\n", "Usage: Please input the number of bodies");
		return 1;
	}
	int N = atoi(argv[1]);
	int i;
	double t0, t1, te, ips;

	struct Body *bodies = (struct Body *) malloc (sizeof(struct Body ) * N);

	randTest (bodies, 0, N);

	wctime(&t0);
	nextPhase_005(bodies, 0, N);
	wctime(&t1);
	te = t1 - t0;
	ips = (K) * (N*N)/te *(1e-6);

	printf("%f, %f, %f, %f\n", ips, te, t0, t1);

	free(bodies);
	return 0;
}
