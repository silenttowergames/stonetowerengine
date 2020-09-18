#pragma once

#include <stdarg.h>
#include "AssetManager.h"

AssetManager AssetManager_Create();

void AssetManager_InitTexture(AssetManager* assetManager, int length);
void AssetManager_AddTexture(AssetManager* assetManager, Texture texture);
void AssetManager_AddTextures(AssetManager* assetManager, int length, ...);

void AssetManager_InitMap(AssetManager* assetManager, int length);
void AssetManager_AddMap(AssetManager* assetManager, TiledJSON map);
void AssetManager_AddMaps(AssetManager* assetManager, int length, ...);

void AssetManager_InitShader(AssetManager* assetManager, int length);
void AssetManager_AddShader(AssetManager* assetManager, Shader map);
void AssetManager_AddShaders(AssetManager* assetManager, int length, ...);

#define textures(length, ...) AssetManager_InitTexture(&app.assetManager, length); AssetManager_AddTextures(&app.assetManager, length, __VA_ARGS__)
#define maps(length, ...) AssetManager_InitMap(&app.assetManager, length); AssetManager_AddMaps(&app.assetManager, length, __VA_ARGS__)
#define shaders(length, ...) AssetManager_InitShader(&app.assetManager, length); AssetManager_AddShaders(&app.assetManager, length, __VA_ARGS__)
