#include <assert.h>
#include "SpriteBatchFunctions.h"

void SpriteBatch_Create(SpriteBatch* spriteBatch)
{
	memset(spriteBatch, 0, sizeof(SpriteBatch));
	
	spriteBatch->vertices = malloc(sizeof(Vertex) * MAX_INDICES); // SpriteBatch.vertices allocate
	spriteBatch->textures = malloc(sizeof(FNA3D_Texture*) * MAX_INDICES); // SpriteBatch.textures allocate
}

bool SpriteBatch_Begin(SpriteBatch* spriteBatch)
{
	assert(!spriteBatch->opened);
	
	spriteBatch->opened = true;
}

void SpriteBatch_AddQuad(SpriteBatch* spriteBatch, Camera* camera, FNA3D_Texture* texture, quad pos, quad src, uint32_t color)
{
	assert(spriteBatch->indicesThisFrame <= (MAX_INDICES - 6));
	
	if(!quad_Intersects(
		camera->position.X - (camera->resolution.X / 2),
		camera->position.X + (camera->resolution.X / 2),
		camera->position.Y - (camera->resolution.Y / 2),
		camera->position.Y + (camera->resolution.Y / 2),
		pos.topLeft.X,
		pos.bottomRight.X,
		pos.topRight.Y,
		pos.bottomLeft.Y
	))
	{
		return;
	}
	
	int i = spriteBatch->indicesThisFrame;
	
	spriteBatch->textures[i + 0] = texture;
	spriteBatch->textures[i + 1] = texture;
	spriteBatch->textures[i + 2] = texture;
	spriteBatch->textures[i + 3] = texture;
	spriteBatch->textures[i + 4] = texture;
	spriteBatch->textures[i + 5] = texture;
	
	spriteBatch->vertices[i + 0].x = pos.topLeft.X;
	spriteBatch->vertices[i + 0].y = pos.topLeft.Y;
	spriteBatch->vertices[i + 0].u = src.topLeft.X;
	spriteBatch->vertices[i + 0].v = src.topLeft.Y;
	spriteBatch->vertices[i + 0].color = color;
	
	spriteBatch->vertices[i + 1].x = pos.topRight.X;
	spriteBatch->vertices[i + 1].y = pos.topRight.Y;
	spriteBatch->vertices[i + 1].u = src.topRight.X;
	spriteBatch->vertices[i + 1].v = src.topRight.Y;
	spriteBatch->vertices[i + 1].color = color;
	
	spriteBatch->vertices[i + 2].x = pos.bottomRight.X;
	spriteBatch->vertices[i + 2].y = pos.bottomRight.Y;
	spriteBatch->vertices[i + 2].u = src.bottomRight.X;
	spriteBatch->vertices[i + 2].v = src.bottomRight.Y;
	spriteBatch->vertices[i + 2].color = color;
	
	spriteBatch->vertices[i + 3].x = pos.bottomRight.X;
	spriteBatch->vertices[i + 3].y = pos.bottomRight.Y;
	spriteBatch->vertices[i + 3].u = src.bottomRight.X;
	spriteBatch->vertices[i + 3].v = src.bottomRight.Y;
	spriteBatch->vertices[i + 3].color = color;
	
	spriteBatch->vertices[i + 4].x = pos.bottomLeft.X;
	spriteBatch->vertices[i + 4].y = pos.bottomLeft.Y;
	spriteBatch->vertices[i + 4].u = src.bottomLeft.X;
	spriteBatch->vertices[i + 4].v = src.bottomLeft.Y;
	spriteBatch->vertices[i + 4].color = color;
	
	spriteBatch->vertices[i + 5].x = pos.topLeft.X;
	spriteBatch->vertices[i + 5].y = pos.topLeft.Y;
	spriteBatch->vertices[i + 5].u = src.topLeft.X;
	spriteBatch->vertices[i + 5].v = src.topLeft.Y;
	spriteBatch->vertices[i + 5].color = color;
	
	spriteBatch->indicesThisFrame += 6;
}

void SpriteBatch_Flush(RenderState* renderState)
{
	if(renderState->spriteBatch.indicesThisFrame <= 0)
	{
		return;
	}
	
	FNA3D_SamplerState samplerState;
	memset(&samplerState, 0, sizeof(samplerState));
	samplerState.addressU = FNA3D_TEXTUREADDRESSMODE_CLAMP;
	samplerState.addressV = FNA3D_TEXTUREADDRESSMODE_CLAMP;
	samplerState.addressW = FNA3D_TEXTUREADDRESSMODE_WRAP;
	samplerState.filter = FNA3D_TEXTUREFILTER_POINT;
	samplerState.maxAnisotropy = 4;
	samplerState.maxMipLevel = 0;
	samplerState.mipMapLevelOfDetailBias = 0;
	
	FNA3D_SetVertexBufferData(renderState->device, renderState->vertexBuffer, 0, renderState->spriteBatch.vertices, sizeof(Vertex) * renderState->spriteBatch.indicesThisFrame, 1, 1, FNA3D_SETDATAOPTIONS_DISCARD);
	renderState->vertexBufferBinding.vertexBuffer = renderState->vertexBuffer;
	
	FNA3D_ApplyVertexBufferBindings(renderState->device, &renderState->vertexBufferBinding, 1, 0, 0);
	
	FNA3D_Texture* texture = NULL;
	int thisTextureStartsAt = 0;
	
	for(int i = 0; i < renderState->spriteBatch.indicesThisFrame; i++)
	{
		if(i == 0 || texture != renderState->spriteBatch.textures[i])
		{
			if(i > 0)
			{
				FNA3D_DrawPrimitives(renderState->device, FNA3D_PRIMITIVETYPE_TRIANGLELIST, thisTextureStartsAt, (i - thisTextureStartsAt) / 3);
				
				thisTextureStartsAt = i;
			}
			
			texture = renderState->spriteBatch.textures[i];
			
			FNA3D_VerifySampler(renderState->device, 0, texture, &samplerState);
		}
	}
	
	FNA3D_DrawPrimitives(renderState->device, FNA3D_PRIMITIVETYPE_TRIANGLELIST, thisTextureStartsAt, (renderState->spriteBatch.indicesThisFrame - thisTextureStartsAt) / 3);
}

bool SpriteBatch_End(SpriteBatch* spriteBatch)
{
	assert(spriteBatch->opened);
	
	spriteBatch->opened = false;
	spriteBatch->indicesThisFrame = 0;
}
