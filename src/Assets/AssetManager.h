#pragma once

#include <flecs.h>
#include "Texture.h"

typedef struct AssetManager
{
	Texture* arrayTexture;
	ecs_map_t* mapTexture;
	int lengthTexture;
	int lengthSoFarTexture;
} AssetManager;
