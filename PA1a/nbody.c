/*
 * nbody.c
 *
 *  Created on: Sep 17, 2013
 *      Author: duozhao
 */

#include <math.h>
#include <stdlib.h> //for rand()
#include <stdint.h>
#include <time.h>
#include "nbody.h"

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

void cal_force(Vec2 *f, Body *target, Body *source){
	Vec2 *tp = &target->position;
	Vec2 *sp = &source->position;

	double dx = tp->x - sp->x;
	double dy = tp->y - sp->y;
	double d2 = dx*dx + dy*dy;
	double dinvSqurtCube = fastInvSqrtCube(d2);
//	double d3 = d2 * sqrt(d2);

	double fac = -G * target->mass * source->mass;
	double K = fac * dinvSqurtCube;
//	double K = -G * target->mass * source->mass / d3;
	f->x = K * dx;
	f->y = K * dy;
}

void nextPhase(Body bodies[N], double t_step, int steps){
	int t, i, j;
	double fx, fy, ax, ay;
	Vec2 force;
	for (t = 0; t < steps; t++){
		for (i = 0; i < N; i++){
			fx = 0;
			fy = 0;
			for (j = 0; j < N; j++)
				if (i != j){
					cal_force(&force, &bodies[i], &bodies[j]);
					fx += force.x;
					fy += force.y;
				}
			ax = fx / bodies[i].mass;
			ay = fy / bodies[i].mass;
			bodies[i].velocity.x += t_step * ax;
			bodies[i].velocity.y += t_step * ay;
		}

		for (i = 0; i < N; i++){
			bodies[i].position.x += t_step * bodies[i].velocity.x;
			bodies[i].position.y += t_step * bodies[i].velocity.y;
		}
	}

}

//void nextPhaseHalf (Body bodies[N], double t_step, int steps, Vec2 forceSratch[N][N]){
//	int t, i, j;
//	Vec2 force;
//	for (t = 0; t < steps; t++){
//		for (i = 0; i < N; i++)
//			for (j = 0; j < i; j++)
//				forceSratch[i][j] = cal_force(&bodies[i], &bodies[j]);
//
//		for (i = 0; i < N; i++){
//			force.x = 0;
//			force.y = 0;
//			for (j = 0; j < i; j++){
//				force.x += forceSratch[i][j].x;
//				force.y += forceSratch[i][j].y;
//			}
//			for (j = i+1; j < N; j++){
//				force.x -= forceSratch[j][i].x;
//				force.y -= forceSratch[j][i].y;
//			}
//
//			bodies[i].acceleration.x = force.x / bodies[i].mass;
//			bodies[i].acceleration.y = force.y / bodies[i].mass;
//
//			bodies[i].position.x += t_step * bodies[i].velocity.x;
//			bodies[i].position.y += t_step * bodies[i].velocity.y;
//
//			bodies[i].velocity.x += t_step * bodies[i].acceleration.x;
//			bodies[i].velocity.y += t_step * bodies[i].acceleration.y;
//		}
//	}
//
//}

void randTest(Body bodies[], int start, int end){
	int i;
	srand (time(NULL));
	for (i = start; i < end; i++){
		bodies[i].mass = 1;
		bodies[i].position.x = 0.1 * i;
		bodies[i].position.y = 0.1 * i;
		bodies[i].velocity.x = 1;
		bodies[i].velocity.y = 1;
	}
}

void randInit(Body bodies[], int start, int end){
	int i;
	srand (time(NULL));
	for (i = start; i < end; i++){
		bodies[i].mass = (float)rand()/(float)RAND_MAX;
		bodies[i].position.x = (float)rand()/(float)RAND_MAX;
		bodies[i].position.y = (float)rand()/(float)RAND_MAX;
		bodies[i].velocity.x = 0 * 1.5 * (float)rand()/(float)RAND_MAX;
		bodies[i].velocity.y = 0 * 1.5 * (float)rand()/(float)RAND_MAX;
	}
}

void bodyCopy(Body target[], Body source[], int start, int end){
	int i = 0;
	for (i = start; i < end; i++){
		target[i].mass = source[i].mass;
		target[i].position.x = source[i].position.x;
		target[i].position.y = source[i].position.y;
		target[i].velocity.x = source[i].velocity.x;
		target[i].velocity.y = source[i].velocity.y;
	}
}

