#pragma once

#include <FNA3D.h>
#include <flecs.h>
#include "../Utilities/int2d.h"

typedef struct Texture
{
	FNA3D_Texture* asset;
	int2d size;
	int2d tilesize;
	int2d border;
	int2d padding;
	const char* key;
	char* filename;
} Texture;
