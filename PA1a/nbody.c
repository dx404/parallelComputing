/*
 * nbody.c
 *
 *  Created on: Sep 17, 2013
 *      Author: duozhao
 */

#include <math.h>
#include <stdlib.h> //for rand()
#include <time.h>
#include "nbody.h"

double distance(Vec2 *t, Vec2 *s) {
	double dx = t->x - s->x;
	double dy = t->y - s->y;
	return sqrt(dx*dx + dy*dy);
}

Vec2 cal_force(Body *target, Body *source){
	Vec2 f;
	double d = distance(&source->position, &target->position);
	double K = G * target->mass * source->mass
				/ (d * d * d);
	f.x = K * (source->position.x - target->position.x);
	f.y = K * (source->position.y - target->position.y);
	return f;
}


void nextPhase(Body bodies[N], double t_step, int steps, Vec2 forceSratch[N][N]){
	int t, i, j;
	for (t = 0; t < steps; t++){
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				if (i != j)
					forceSratch[i][j] = cal_force(&bodies[i], &bodies[j]);

		Vec2 force;
		for (i = 0; i < N; i++){
			force.x = 0;
			force.y = 0;
			for (j = 0; j < N; j++)
				if (i != j){
					force.x += forceSratch[i][j].x;
					force.y += forceSratch[i][j].y;
				}
			bodies[i].acceleration.x = force.x / bodies[i].mass;
			bodies[i].acceleration.y = force.y / bodies[i].mass;

			bodies[i].position.x += t_step * bodies[i].velocity.x;
			bodies[i].position.y += t_step * bodies[i].velocity.y;

			bodies[i].velocity.x += t_step * bodies[i].acceleration.x;
			bodies[i].velocity.y += t_step * bodies[i].acceleration.y;
		}
	}

}

void nextPhaseHalf (Body bodies[N], double t_step, int steps, Vec2 forceSratch[N][N]){
	int t, i, j;
	Vec2 force;
	for (t = 0; t < steps; t++){
		for (i = 0; i < N; i++)
			for (j = 0; j < i; j++)
				forceSratch[i][j] = cal_force(&bodies[i], &bodies[j]);

		for (i = 0; i < N; i++){
			force.x = 0;
			force.y = 0;
			for (j = 0; j < i; j++){
				force.x += forceSratch[i][j].x;
				force.y += forceSratch[i][j].y;
			}
			for (j = i+1; j < N; j++){
				force.x -= forceSratch[j][i].x;
				force.y -= forceSratch[j][i].y;
			}

			bodies[i].acceleration.x = force.x / bodies[i].mass;
			bodies[i].acceleration.y = force.y / bodies[i].mass;

			bodies[i].position.x += t_step * bodies[i].velocity.x;
			bodies[i].position.y += t_step * bodies[i].velocity.y;

			bodies[i].velocity.x += t_step * bodies[i].acceleration.x;
			bodies[i].velocity.y += t_step * bodies[i].acceleration.y;
		}
	}

}

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
		target[i].acceleration.x = source[i].acceleration.x;
		target[i].acceleration.y = source[i].acceleration.y;
	}
}

