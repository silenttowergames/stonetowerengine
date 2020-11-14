#pragma once

#include "../Utilities/float2d.h"
#include "../Utilities/int2d.h"

typedef struct Camera
{
	int2d resolution;
	float2d position;
	float2d zoom;
	float rotation;
	float projection[16];
} Camera;
