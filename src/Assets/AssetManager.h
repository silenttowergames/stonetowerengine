#pragma once

#include <flecs.h>
#include <lua.h>
#include "LuaScript.h"
#include "Shader.h"
#include "Texture.h"
#include "TiledJSON.h"

// This is really ugly lol
// That could certainly be pared down
// Maybe a map container type?
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
	
	lua_State* lua;
	LuaScript* arrayLua;
	ecs_map_t* mapLua;
	int lengthLua;
	int lengthSoFarLua;
} AssetManager;
