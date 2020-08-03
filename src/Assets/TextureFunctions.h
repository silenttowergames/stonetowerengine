#pragma once

#include "Texture.h"

Texture Texture_NewFromData(FNA3D_Device* device, int width, int height, stbi_uc* pixels, int channels, bool isRenderTarget);
Texture Texture_NewBlank(FNA3D_Device* device, int width, int height, int channels, bool isRenderTarget);
Texture Texture_Load(FNA3D_Device* device, const char* key);
