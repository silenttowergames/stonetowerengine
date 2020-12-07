#pragma once

#include <flecs.h>
#include "Vertex.h"

#ifndef MAX_SPRITES
#define MAX_SPRITES 10000
#endif

#ifndef MAX_INDICES
#define MAX_INDICES MAX_SPRITES * 6
#endif

typedef struct SpriteBatch
{
	Vertex* vertices;
	FNA3D_Texture** textures;
	int indicesThisFrame;
	bool opened;
} SpriteBatch;
