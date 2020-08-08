#pragma once

#include <flecs.h>
#include "Vertex.h"

#ifndef MAX_SPRITES
#define MAX_SPRITES 1024
#endif

#ifndef MAX_INDICES
#define MAX_INDICES MAX_SPRITES * 6
#endif

typedef struct SpriteBatch
{
	Vertex vertices[MAX_INDICES];
	FNA3D_Texture* textures[MAX_INDICES];
	int indicesThisFrame;
	bool opened;
} SpriteBatch;
