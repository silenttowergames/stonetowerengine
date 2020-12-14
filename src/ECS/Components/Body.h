#pragma once

#include "../../Utilities/float2d.h"

typedef struct Body
{
	float2d position;
	float2d velocity;
	float2d initialVelocity;
	float2d effectiveVelocity;
} Body;

#define bodyEasy(x, y) { { x, y, }, { 0, 0, }, { 0, 0, }, { 0, 0, }, }
