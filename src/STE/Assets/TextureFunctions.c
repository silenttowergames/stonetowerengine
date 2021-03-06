#include <FNA3D_Image.h>
#include "TextureFunctions.h"
#include "ASEpriteJSONFunctions.h"

Texture Texture_NewFromData(FNA3D_Device* device, int width, int height, unsigned char* pixels, int channels, bool isRenderTarget)
{
	Texture texture;
	memset(&texture, 0, sizeof(Texture));
	texture.size.X = width;
	texture.size.Y = height;
	texture.tilesize = texture.size;
	
	FNA3D_Texture* asset = FNA3D_CreateTexture2D(device, FNA3D_SURFACEFORMAT_COLOR, width, height, 1, isRenderTarget);
	FNA3D_SetTextureData2D(device, asset, 0, 0, width, height, 0, pixels, width * height * channels);
	texture.asset = asset;
	
	return texture;
}

Texture Texture_NewBlank(FNA3D_Device* device, int width, int height, int channels, bool isRenderTarget)
{
	size_t size = width * height * channels;
	size_t sizeWithType = sizeof(unsigned char) * size;
	
	unsigned char* pixels = malloc(sizeWithType);
	memset(pixels, 0xFF, sizeWithType);
	
	Texture texture = Texture_NewFromData(device, width, height, pixels, channels, isRenderTarget);
	
	stbi_image_free(pixels);
	
	return texture;
}

Texture Texture_Load(ApplicationState* app, const char* key)
{
	char* filename;
	int2d size;
	int channels;
	
	filename = malloc(sizeof(char) * (strlen(key) + 20));
	sprintf(filename, "assets/sprites/%s.png", key);
	
	unsigned char* pixels = stbi_load(filename, &size.X, &size.Y, &channels, 4);
	
	if(pixels == NULL)
	{
		Logger_Log(&app->logger, "Texture Not Found", filename);
		
		assert(pixels != NULL);
	}
	
	Texture texture = Texture_NewFromData(app->renderState.device, size.X, size.Y, pixels, channels, false);
	texture.key = key;
	texture.filename = filename;
	
	texture.aseprite = ASEpriteJSON_Load(app, key);
	
	stbi_image_free(pixels);
	
	return texture;
}

Texture Texture_Create(ApplicationState* app, const char* key, int tilesizeX, int tilesizeY, int paddingX, int paddingY, int borderX, int borderY)
{
	Texture texture = Texture_Load(app, key);
	
	texture.tilesize.X = tilesizeX;
	texture.tilesize.Y = tilesizeY;
	texture.padding.X = paddingX;
	texture.padding.Y = paddingY;
	texture.border.X = borderX;
	texture.border.Y = borderY;
	
	return texture;
}

void Texture_Free(FNA3D_Device* device, Texture* texture)
{
	if(texture->aseprite.loaded)
	{
		ASEpriteJSON_Free(&texture->aseprite);
	}
	
	free(texture->filename);
	
	FNA3D_AddDisposeTexture(device, texture->asset);
}
