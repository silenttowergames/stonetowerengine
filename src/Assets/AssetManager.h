#pragma once

#include <flecs.h>
#include "Shader.h"
#include "Texture.h"
#include "TiledJSON.h"

typedef struct AssetManager
{
	Texture* arrayTexture;
	ecs_map_t* mapTexture;
	int lengthTexture;
	int lengthSoFarTexture;
	
	TiledJSON* arrayTiled;
	ecs_map_t* mapTiled;
	int lengthTiled;
	int lengthSoFarTiled;
	
	Shader* arrayShader;
	ecs_map_t* mapShader;
	int lengthShader;
	int lengthSoFarShader;
} AssetManager;
