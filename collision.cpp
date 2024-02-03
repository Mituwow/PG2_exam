#define _USE_MATH_DEFINES
#include <math.h>
#include "collision.h"

float Collision::Distance(float x1, float y1, float x2, float y2)
{
	float X = (x2 - x1) * (x2 - x1);
	float Y = (y2 - y1) * (y2 - y1);
	return sqrtf(X + Y);
}

void Collision::Checker(Transform a, int aRadius, Transform b, int bRadius)
{
	distance_ = Distance(a.x, a.y, b.x, b.y);
	if (distance_ < aRadius + bRadius) {
		checker_ = true;
	}
	if (distance_ > aRadius + bRadius) {
		checker_ = false;
	}
}
