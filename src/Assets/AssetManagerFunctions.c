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
	
	ecs_map_set(assetManager->mapTexture, texture.key, &assetManager->arrayTexture[assetManager->lengthSoFarTexture]);
	
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
