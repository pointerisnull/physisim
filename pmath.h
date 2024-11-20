#ifndef PMATH_H
#define PMATH_H

typedef struct {
	float x;
	float y;
	float z;
} Vec;


float magnitude(Vec a);
float distance(Vec a, Vec b);
float angle(Vec a, Vec b);
float dot(Vec a, Vec b);
Vec cross(Vec a, Vec b);
Vec normalize(Vec a);

const float g   = 9.81;
const float G   = 6.6743e-11f;
const float e   = 1.602e-19;
const float me  = 9.11e-31;
const float mp  = 1.67e-27;
const float k   = 8.99e9;

#endif
