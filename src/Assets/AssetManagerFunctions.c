#include "AssetManagerFunctions.h"

AssetManager AssetManager_Create()
{
	AssetManager assetManager;
	memset(&assetManager, 0, sizeof(AssetManager));
	
	assetManager.lua = luaL_newstate();
	luaL_openlibs(assetManager.lua);
	
	return assetManager;
}

void AssetManager_Destroy(AssetManager* assetManager)
{
	lua_close(assetManager->lua);
}

void AssetManager_InitTexture(AssetManager* assetManager, int length)
{
	assetManager->arrayTexture = malloc(sizeof(Texture) * length);
	assetManager->mapTexture = ecs_map_new(Texture, length);
	assetManager->lengthTexture = length;
	assetManager->lengthSoFarTexture = 0;
}

void AssetManager_AddTexture(AssetManager* assetManager, Texture texture)
{
	assetManager->arrayTexture[assetManager->lengthSoFarTexture] = texture;
	
	mapSet(assetManager->mapTexture, texture.key, &assetManager->arrayTexture[assetManager->lengthSoFarTexture]);
	
	assetManager->lengthSoFarTexture++;
}

void AssetManager_AddTextures(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddTexture(assetManager, va_arg(args, Texture));
	}
	
	va_end(args);
}

void AssetManager_InitMap(AssetManager* assetManager, int length)
{
	assetManager->arrayTiled = malloc(sizeof(TiledJSON) * length);
	assetManager->mapTiled = ecs_map_new(TiledJSON, length);
	assetManager->lengthTiled = length;
	assetManager->lengthSoFarTiled = 0;
}

void AssetManager_AddMap(AssetManager* assetManager, TiledJSON map)
{
	assetManager->arrayTiled[assetManager->lengthSoFarTiled] = map;
	
	mapSet(assetManager->mapTiled, map.key, &assetManager->arrayTiled[assetManager->lengthSoFarTiled]);
	
	assetManager->lengthSoFarTiled++;
}

void AssetManager_AddMaps(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddMap(assetManager, va_arg(args, TiledJSON));
	}
	
	va_end(args);
}

void AssetManager_InitShader(AssetManager* assetManager, int length)
{
	assetManager->arrayShader = malloc(sizeof(Shader) * length);
	assetManager->mapShader = ecs_map_new(Shader, length);
	assetManager->lengthShader = length;
	assetManager->lengthSoFarShader = 0;
}

void AssetManager_AddShader(AssetManager* assetManager, Shader shader)
{
	assetManager->arrayShader[assetManager->lengthSoFarShader] = shader;
	
	mapSet(assetManager->mapShader, shader.key, &assetManager->arrayShader[assetManager->lengthSoFarShader]);
	
	assetManager->lengthSoFarShader++;
}

void AssetManager_AddShaders(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddShader(assetManager, va_arg(args, Shader));
	}
	
	va_end(args);
}

void AssetManager_InitLua(AssetManager* assetManager, int length)
{
	assetManager->arrayLua = malloc(sizeof(LuaScript) * length);
	assetManager->mapLua = ecs_map_new(LuaScript, length);
	assetManager->lengthLua = length;
	assetManager->lengthSoFarLua = 0;
}

void AssetManager_AddLua(AssetManager* assetManager, LuaScript script)
{
	assetManager->arrayLua[assetManager->lengthSoFarLua] = script;
	
	mapSet(assetManager->mapLua, script.key, &assetManager->arrayLua[assetManager->lengthSoFarLua]);
	
	assetManager->lengthSoFarLua++;
}

void AssetManager_AddLuas(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddLua(assetManager, va_arg(args, LuaScript));
	}
	
	va_end(args);
}

#define getTexture(key) mapGet(app->assetManager.mapTexture, key, Texture)
