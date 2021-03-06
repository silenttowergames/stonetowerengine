#pragma once

#include "Texture.h"

Texture Texture_NewFromData(FNA3D_Device* device, int width, int height, unsigned char* pixels, int channels, bool isRenderTarget);
Texture Texture_NewBlank(FNA3D_Device* device, int width, int height, int channels, bool isRenderTarget);
Texture Texture_Load(ApplicationState* app, const char* key);
Texture Texture_Create(ApplicationState* app, const char* key, int tilesizeX, int tilesizeY, int paddingX, int paddingY, int borderX, int borderY);
void Texture_Free(FNA3D_Device* device, Texture* texture);
