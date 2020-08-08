#pragma once

#include <stdarg.h>
#include "AssetManager.h"

AssetManager AssetManager_Create();

void AssetManager_InitTexture(AssetManager* assetManager, int length);
void AssetManager_AddTexture(AssetManager* assetManager, Texture texture);
void AssetManager_AddTextures(AssetManager* assetManager, int length, ...);

#define textures(length, ...) AssetManager_InitTexture(&app.assetManager, length); AssetManager_AddTextures(&app.assetManager, length, __VA_ARGS__)
