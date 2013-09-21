#ifndef NBODY_H
#define NBODY_H

#define N 1024
#define G 0.001
#define dt 0.001
#define t_end 0.004

typedef struct{
	double x, y;
} Vec2;

typedef struct{
	double mass;
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
} Body;

double distance(Vec2 *t, Vec2 *s);

Vec2 cal_force(Body *target, Body *source);

void nextPhase(Body bodies[N], double t_step, int steps, Vec2 forceSratch[N][N]);

void nextPhaseHalf (Body bodies[N], double t_step, int steps, Vec2 forceSratch[N][N]);

void randInit(Body bodies[], int start, int end);

void bodyCopy(Body target[], Body source[], int start, int end);

void bodiesPrint(Body bodies[], int start, int end);

#endif
