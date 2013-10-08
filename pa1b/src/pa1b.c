/*
 ============================================================================
 Name        : pa1b.c
 Author      : Duo Zhao
 Version     : v4.0
 Copyright   : COMP 633 Parallel Computing PA1b
 Description : N-Body Problems
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define G 1.0
#define dt 0.001

struct Vec2 { double x, y;};

struct NBody {
	double *m;
	struct Vec2 *p;
	struct Vec2 *v;
};

void printMomentum(struct NBody *nBody, int num){
	double mvx = 0, mvy = 0;
	for (int i = 0; i < num; i++){
		mvx += nBody->m[i] * nBody->v[i].x;
		mvy += nBody->m[i] * nBody->v[i].y;
	}
	printf("---mvx=%f, mvy=%f\n", mvx, mvy);
}

void wctime(double *t) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	*t = tv.tv_sec + (1E-6) * tv.tv_usec;
}

void re_scale_Normalize(double *dx, double *dy, double sk){
	double d2  = *dx * *dx + *dy * *dy;
	double d3 = d2 * sqrt(d2);
	*dx =  *dx * sk/d3;
	*dy =  *dx * sk/d3;
}

void sanityInit(struct NBody *nBody);

void init_NBody_rand(struct NBody *nBody, int num){
	double *m = (double *) malloc (sizeof(double) * num);
	struct Vec2 *p = (struct Vec2 *) malloc (sizeof(struct Vec2) * num);
	struct Vec2 *v = (struct Vec2 *) malloc (sizeof(struct Vec2) * num);

	srand (time(NULL));
	for (int i = 0; i < num; i++)
		m[i] = (double)rand()/(double)RAND_MAX;

	for (int i = 0; i < num; i++){
		p[i].x = (double)rand()/(double)RAND_MAX;
		p[i].y = (double)rand()/(double)RAND_MAX;
	}

	for (int i = 0; i < num; i++){
		v[i].x = (double)rand()/(double)RAND_MAX;
		v[i].y = (double)rand()/(double)RAND_MAX;
	}

	nBody->m = m;
	nBody->p = p;
	nBody->v = v;
}

void free_Nbody(struct NBody *nBody){
	free (nBody->m);
	free (nBody->p);
	free (nBody->v);
}

void nBodyPrintCSV(struct NBody *nBody, int start, int end);

void nextPhase_all_seq(struct NBody *nBody, int num, int steps, double *clock_record){
	wctime(clock_record++);
	struct Vec2 *a = malloc (sizeof(struct Vec2) * num);
	for (int t = 0; t < steps; t++){
		for (int i = 0; i < num; i++){
			double ipx = nBody->p[i].x;
			double ipy = nBody->p[i].y;
			double iax = 0;
			double iay = 0;
			for (int j = 0; j < num; j++){
				if (j == i)
					continue;
				double m = nBody->m[j];
				double dx = nBody->p[j].x - ipx;
				double dy = nBody->p[j].y - ipy;
				double d2inv = 1/(dx * dx + dy * dy);
				double md3inv = m * d2inv * sqrt(d2inv);
				iax += md3inv * dx;
				iay += md3inv * dy;

			}
			a[i].x = iax;
			a[i].y = iay;
		}

		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
		}

		for (int i = 0; i < num; i++){
			nBody->v[i].x += dt * a[i].x;
			nBody->v[i].y += dt * a[i].y;
		}
	}
	wctime(clock_record++);
	free(a);
}

void nextPhase_all_para(struct NBody *nBody, int num, int steps, double *clock_record){
	wctime(clock_record++);
	struct Vec2 *a = malloc (sizeof(struct Vec2) * num);

	for (int t = 0; t < steps; t++){
		//#pragma omp parallel for num_threads(16)
		for (int i = 0; i < num; i++){
			double ipx = nBody->p[i].x;
			double ipy = nBody->p[i].y;
			double iax = 0;
			double iay = 0;

			#pragma omp parallel for firstprivate(i) reduction(+:iax, iay) num_threads(8)
			for (int j = 0; j < num; j++){
				if (j == i)
					continue;
				double m = nBody->m[j];
				double dx = nBody->p[j].x - ipx;
				double dy = nBody->p[j].y - ipy;
				double d2inv = 1/(dx * dx + dy * dy);
				double md3inv = m * d2inv * sqrt(d2inv);
				iax += md3inv * dx;
				iay += md3inv * dy;

			}
			a[i].x = iax;
			a[i].y = iay;
		}

		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
		}

		for (int i = 0; i < num; i++){
			nBody->v[i].x += dt * a[i].x;
			nBody->v[i].y += dt * a[i].y;
		}
	}
	wctime(clock_record++);
	free(a);
}

void nextPhase_half_seq(struct NBody *nBody, int num, int steps, double *clock_record){
	struct Vec2 *a = calloc (num, sizeof(struct Vec2));
	wctime(clock_record++);
	for (int t = 0; t < steps; t++){
		for (int i = 0; i < num; i++){
			double im  = nBody->m[i];
			double ipx = nBody->p[i].x;
			double ipy = nBody->p[i].y;
			double iax = 0;
			double iay = 0;

			for (int j = i + 1; j < num; j++){
				double jm = nBody->m[j];
				double dx = nBody->p[j].x - ipx;
				double dy = nBody->p[j].y - ipy;
				double d2inv = 1/(dx * dx + dy * dy);
				double d3inv = d2inv * sqrt(d2inv);
				double imd3inv = im * d3inv;
				double jmd3inv = jm * d3inv;

				iax += jmd3inv * dx;
				iay += jmd3inv * dy;

				a[j].x -= imd3inv * dx;
				a[j].y -= imd3inv * dy;

			}
			a[i].x += iax;
			a[i].y += iay;
		}

		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
			nBody->v[i].x += dt * a[i].x;
			nBody->v[i].y += dt * a[i].y;
			a[i].x = a[i].y = 0;
		}

	}
	wctime(clock_record++);
	free(a);
}

void nextPhase_half_para(struct NBody *nBody, int num, int steps, double *clock_record){
	struct Vec2 *a = calloc (num, sizeof(struct Vec2));
	wctime(clock_record++);
	for (int t = 0; t < steps; t++){

		for (int i = 0; i < num; i++){
			double im  = nBody->m[i];
			double ipx = nBody->p[i].x;
			double ipy = nBody->p[i].y;
			double iax = 0;
			double iay = 0;

			#pragma omp parallel for firstprivate(i) num_threads(8)
			for (int j = i + 1; j < num; j++){
				double jm = nBody->m[j];
				double dx = nBody->p[j].x - ipx;
				double dy = nBody->p[j].y - ipy;
				double d2inv = 1/(dx * dx + dy * dy);
				double d3inv = d2inv * sqrt(d2inv);
				double imd3inv = im * d3inv;
				double jmd3inv = jm * d3inv;

				iax += jmd3inv * dx;
				iay += jmd3inv * dy;

				a[j].x -= imd3inv * dx;
				a[j].y -= imd3inv * dy;

			}
			a[i].x += iax;
			a[i].y += iay;
		}

		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
			nBody->v[i].x += dt * a[i].x;
			nBody->v[i].y += dt * a[i].y;
			a[i].x = a[i].y = 0;
		}

	}
	wctime(clock_record++);
	free(a);
}

void nextPhase_half_para_003(struct NBody *nBody, int num, int steps, double *clock_record){
	struct Vec2 *a = calloc (num, sizeof(struct Vec2));
	wctime(clock_record++);

	for (int t = 0; t < steps; t++){
		#pragma omp parallel for schedule(dynamic) num_threads(5)
		for (int i = 0; i < num; i++){
			double im  = nBody->m[i];
			double ipx = nBody->p[i].x;
			double ipy = nBody->p[i].y;
			double iax = 0;
			double iay = 0;

//			#pragma omp parallel for reduction(+:iax, iay) num_threads(16)
			for (int j = i + 1; j < num; j++){
				double jm = nBody->m[j];
				double dx = nBody->p[j].x - ipx;
				double dy = nBody->p[j].y - ipy;
				double d2inv = 1/(dx * dx + dy * dy);
				double d3inv = d2inv * sqrt(d2inv);
				double imd3inv = im * d3inv;
				double jmd3inv = jm * d3inv;

				iax += jmd3inv * dx;
				iay += jmd3inv * dy;

			#pragma omp atomic
				a[j].x -= imd3inv * dx;
			#pragma omp atomic
				a[j].y -= imd3inv * dy;

			}
			#pragma omp atomic
			a[i].x += iax;
			#pragma omp atomic
			a[i].y += iay;
		}

		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
			nBody->v[i].x += dt * a[i].x;
			nBody->v[i].y += dt * a[i].y;
			a[i].x = a[i].y = 0;
		}

	}
	wctime(clock_record++);
	free(a);
}

void nextPhase_half_para_002(struct NBody *nBody, int num, int steps, double *clock_record){
	struct Vec2 **a = (struct Vec2 **) malloc (num * sizeof(struct Vec2 *));
	for (int i = 0; i < num; i++){
		a[i] = (struct Vec2 *) malloc (num * sizeof(struct Vec2));
	}

	struct Vec2 *ai = (struct Vec2 *) malloc (num * sizeof(struct Vec2));

	omp_set_num_threads(8);
	wctime(clock_record++);
	for (int t = 0; t < steps; t++){

		#pragma omp parallel for
		for (int i = 0; i < num; i++){
			for (int j = i + 1; j < num; j++){
				double im  = nBody->m[i];
				double ipx = nBody->p[i].x;
				double ipy = nBody->p[i].y;

				double jm  = nBody->m[j];
				double jpx = nBody->p[j].x;
				double jpy = nBody->p[j].y;

				double dx = jpx - ipx;
				double dy = jpy - ipy;

				double d2inv = 1/(dx * dx + dy * dy);
				double d3inv = d2inv * sqrt(d2inv);

				a[i][j].x = jm * d3inv;
				a[i][j].y = jm * d3inv;

				a[j][i].x = - im * d3inv;
				a[j][i].y = - im * d3inv;

			}
		}

//		#pragma omp parallel for
		for (int i = 0; i < num; i++){
			a[i][i].x = a[i][i].y = 0;
		}

//		#pragma omp parallel for
		for (int i = 0; i < num; i++){
			double ai_sum_x = 0;
			double ai_sum_y = 0;

//			#pragma omp parallel for reduction(+: ai_sum_x, ai_sum_y)
			for (int j = 0; j < num; j++){
				ai_sum_x += a[i][j].x;
				ai_sum_y += a[i][j].y;
			}
			ai[i].x = ai_sum_x;
			ai[i].y = ai_sum_y;
		}

//		#pragma omp parallel for
		for (int i = 0; i < num; i++){
			nBody->p[i].x += dt * nBody->v[i].x;
			nBody->p[i].y += dt * nBody->v[i].y;
			nBody->v[i].x += dt * ai[i].x;
			nBody->v[i].y += dt * ai[i].y;
		}

	}
	wctime(clock_record++);
	free(ai);
	free(a);
}

#define N 5000
#define K 4
int main (int argc, char *argv[]) {
	struct NBody nBody;
	double clock_record[2];
//	sanityInit(&nBody);
	init_NBody_rand(&nBody, N);
	printMomentum(&nBody, N);
	nextPhase_half_para_003(&nBody, N, K, clock_record);

	double te = clock_record[1] - clock_record[0];

	printMomentum(&nBody, N);
//	nBodyPrintCSV(&nBody, 0, N);

	printf("8.0, %d, %d, %f, %f\n", K, N, te, (K)*(N * N)/te * (1e-6));

	free_Nbody(&nBody);
	return 0;
}

void sanityInit(struct NBody *nBody){
	nBody->m = (double *) malloc (sizeof(double) * 4);
	nBody->p = (struct Vec2 *) malloc (sizeof(struct Vec2) * 4);
	nBody->v = (struct Vec2 *) malloc (sizeof(struct Vec2) * 4);

	nBody->m[0] = 1.0;
	nBody->m[1] = 0.75;
	nBody->m[2] = 0.5;
	nBody->m[3] = 0.25;

	nBody->p[0].x = 0.0;
	nBody->p[0].y = 0.0;
	nBody->p[1].x = 0.25;
	nBody->p[1].y = 0.25;
	nBody->p[2].x = 0.5;
	nBody->p[2].y = 0.5;
	nBody->p[3].x = 0.75;
	nBody->p[3].y = 0.75;

	nBody->v[0].x = 0.0;
	nBody->v[0].y = 0.0;
	nBody->v[1].x = -0.25;
	nBody->v[1].y = 0.25;
	nBody->v[2].x = -0.5;
	nBody->v[2].y = 0.5;
	nBody->v[3].x = -0.75;
	nBody->v[3].y = 0.75;
}

void nBodyPrintCSV(struct NBody *nBody, int start, int end){
	printf("\n");
	for (int i = start; i < end; i++){
		printf("%f, %f, %f, %f, %f\n",
				nBody->m[i],
				nBody->p[i].x, nBody->p[i].y,
				nBody->v[i].x, nBody->v[i].y
			);
	}
	printf("\n");

}
