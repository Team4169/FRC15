#ifndef POLAR_COORD_HEADER_GUARD
#define POLAR_COORD_HEADER_GUARD

#include "Vector2.h"
#include "Math.h"
#include "Angle.h"

struct PolarCoord{
	Angle angle;
	float magnitude;

	PolarCoord(Angle angle, float magnitude): angle(angle), magnitude(magnitude){}
	PolarCoord(float angle, float magnitude): angle(angle), magnitude(magnitude){}
	PolarCoord(Vector2 vector2):
		angle(atan2(vector2.y, vector2.x)),
		magnitude(sqrt(pow(vector2.x, 2) + pow(vector2.y, 2))){}
};

#endif
