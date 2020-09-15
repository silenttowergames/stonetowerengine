#include "RenderOffsetFunctions.h"

float2d RenderOffset_Sine(int index, int duration)
{
	float2d offset;
	
	offset.X = 0;
	
	offset.Y += min(0, sinf((duration - index) * 0.1f) * 5);
	
	return offset;
}
