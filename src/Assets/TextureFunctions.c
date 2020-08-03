#include <FNA3D_Image.h>
#include "TextureFunctions.h"

Texture Texture_NewFromData(FNA3D_Device* device, int width, int height, stbi_uc* pixels, int channels, bool isRenderTarget)
{
	Texture texture;
	memset(&texture, 0, sizeof(Texture));
	texture.size.X = width;
	texture.size.Y = height;
	texture.tilesize = texture.size;
	
	FNA3D_Texture* asset = FNA3D_CreateTexture2D(device, FNA3D_SURFACEFORMAT_COLOR, width, height, 1, isRenderTarget);
	FNA3D_SetTextureData2D(device, asset, FNA3D_SURFACEFORMAT_COLOR, 0, 0, width, height, 0, pixels, width * height * channels);
	texture.asset = asset;
	
	return texture;
}

Texture Texture_NewBlank(FNA3D_Device* device, int width, int height, int channels, bool isRenderTarget)
{
	size_t size = width * height * channels;
	size_t sizeWithType = sizeof(stbi_uc) * size;
	
	stbi_uc* pixels = malloc(sizeWithType);
	memset(pixels, 0xFF, sizeWithType);
	
	return Texture_NewFromData(device, width, height, pixels, channels, isRenderTarget);
}

Texture Texture_Load(FNA3D_Device* device, const char* key, bool isRenderTarget)
{
	//
}
