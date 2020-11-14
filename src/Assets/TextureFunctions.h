#pragma once

#include "../StoneTower.h"
#include "Texture.h"
#include "../vendor/stb_image.h"

Texture Texture_NewFromData(FNA3D_Device* device, int width, int height, stbi_uc* pixels, int channels, bool isRenderTarget);
Texture Texture_NewBlank(FNA3D_Device* device, int width, int height, int channels, bool isRenderTarget);
Texture Texture_Load(FNA3D_Device* device, const char* key);
Texture Texture_Create(FNA3D_Device* device, const char* key, int tilesizeX, int tilesizeY, int paddingX, int paddingY, int borderX, int borderY);
void Texture_Free(FNA3D_Device* device, Texture* texture);
