#include <assert.h>
#include "SpriteBatchFunctions.h"

void SpriteBatch_Create(SpriteBatch* spriteBatch)
{
	memset(spriteBatch, 0, sizeof(SpriteBatch));
}

bool SpriteBatch_Begin(SpriteBatch* spriteBatch)
{
	assert(!spriteBatch->opened);
	
	spriteBatch->opened = true;
}

void SpriteBatch_AddQuad(SpriteBatch* spriteBatch, quad q)
{
	assert(spriteBatch->indicesThisFrame <= (MAX_INDICES - 6));
	
	int i = spriteBatch->indicesThisFrame;
	
	uint32_t color = 0xFFFFFFFF;
	
	spriteBatch->vertices[i + 0].x = q.topLeft.X;
	spriteBatch->vertices[i + 0].y = q.topLeft.Y;
	spriteBatch->vertices[i + 0].u = 0;
	spriteBatch->vertices[i + 0].v = 0;
	spriteBatch->vertices[i + 0].color = color;
	
	spriteBatch->vertices[i + 1].x = q.topRight.X;
	spriteBatch->vertices[i + 1].y = q.topRight.Y;
	spriteBatch->vertices[i + 1].u = 32;
	spriteBatch->vertices[i + 1].v = 0;
	spriteBatch->vertices[i + 1].color = color;
	
	spriteBatch->vertices[i + 2].x = q.bottomRight.X;
	spriteBatch->vertices[i + 2].y = q.bottomRight.Y;
	spriteBatch->vertices[i + 2].u = 32;
	spriteBatch->vertices[i + 2].v = 32;
	spriteBatch->vertices[i + 2].color = color;
	
	spriteBatch->vertices[i + 3].x = q.bottomRight.X;
	spriteBatch->vertices[i + 3].y = q.bottomRight.Y;
	spriteBatch->vertices[i + 3].u = 32;
	spriteBatch->vertices[i + 3].v = 32;
	spriteBatch->vertices[i + 3].color = color;
	
	spriteBatch->vertices[i + 4].x = q.bottomLeft.X;
	spriteBatch->vertices[i + 4].y = q.bottomLeft.Y;
	spriteBatch->vertices[i + 4].u = 0;
	spriteBatch->vertices[i + 4].v = 32;
	spriteBatch->vertices[i + 4].color = color;
	
	spriteBatch->vertices[i + 5].x = q.topLeft.X;
	spriteBatch->vertices[i + 5].y = q.topLeft.Y;
	spriteBatch->vertices[i + 5].u = 0;
	spriteBatch->vertices[i + 5].v = 0;
	spriteBatch->vertices[i + 5].color = color;
	
	spriteBatch->indicesThisFrame += 6;
}

void SpriteBatch_Flush(RenderState* renderState)
{
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
	
	// Set texture
	FNA3D_VerifySampler(renderState->device, 0, renderState->texture.asset, &samplerState);
	
	// Draw
	FNA3D_DrawPrimitives(renderState->device, FNA3D_PRIMITIVETYPE_TRIANGLELIST, 0, (renderState->spriteBatch.indicesThisFrame / 3));
}

bool SpriteBatch_End(SpriteBatch* spriteBatch)
{
	assert(spriteBatch->opened);
	
	spriteBatch->opened = false;
	spriteBatch->indicesThisFrame = 0;
}
