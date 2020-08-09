#pragma once

#include "../Rendering/Animation.h"
#include "../Utilities/int2d.h"

typedef struct ASEpriteJSON
{
	const char* key;
	char* filename;
	int2d size;
    Animation* animations;
    int animationsCount;
    Frame* frames;
    int framesCount;
} ASEpriteJSON;
