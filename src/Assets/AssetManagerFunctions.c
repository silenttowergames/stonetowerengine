#include "AssetManagerFunctions.h"

AssetManager AssetManager_Create()
{
	AssetManager assetManager;
	memset(&assetManager, 0, sizeof(AssetManager));
	
	return assetManager;
}

void AssetManager_InitTexture(AssetManager* assetManager, int length)
{
	assetManager->arrayTexture = malloc(sizeof(Texture) * length);
	assetManager->mapTexture = ecs_map_new(Texture, length);
	assetManager->lengthTexture = length;
}

void AssetManager_AddTexture(AssetManager* assetManager, Texture texture)
{
	assetManager->arrayTexture[assetManager->lengthSoFarTexture] = texture;
	
	ecs_map_set(assetManager->mapTexture, hashlittle(texture.key, strlen(texture.key), 0), &assetManager->arrayTexture[assetManager->lengthSoFarTexture]);
	
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
}

void AssetManager_AddMap(AssetManager* assetManager, TiledJSON map)
{
	assetManager->arrayTiled[assetManager->lengthSoFarTiled] = map;
	
	ecs_map_set(assetManager->mapTiled, hashlittle(map.key, strlen(map.key), 0), &assetManager->arrayTiled[assetManager->lengthSoFarTiled]);
	
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

#define getTexture(key) ecs_map_get(app->assetManager.mapTexture, Texture, hashlittle(key, strlen(key), 0))
