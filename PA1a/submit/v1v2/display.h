#ifndef DISPLAY_H
#define DISPLAY_H

struct BodyState{
	double mvx, mvy;
	double energy;
};

void bodiesPrint(Body bodies[], int start, int end);

struct BodyState getState(Body *body, int size);

void statePrint(struct BodyState *s);

void wctime(double *);

#endif
