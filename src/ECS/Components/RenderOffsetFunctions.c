#include "RenderOffsetFunctions.h"

float2d RenderOffset_Sine(int index, int duration)
{
	float2d offset;
	
	offset.X = 0;
	
	offset.Y += fmin(0, sinf((duration - index) * 0.1f) * 5);
	
	return offset;
}

float2d RenderOffset_Random(int index, int duration)
{
	float2d offset;
	
	offset.X = ((rand() % 4) - 2) * 0.25f;
	offset.Y = ((rand() % 4) - 2) * 0.25f;
	
	return offset;
}

float2d RenderOffset_Stagger(int index, int duration)
{
	float2d offset;
	
	offset.X = 0;
	offset.Y = 0.5f * (index % 2 == 0 ? 1 : -1);
	
	return offset;
}
