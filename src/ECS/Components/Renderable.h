#pragma once

#include "../../Assets/Texture.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/float2d.h"
#include "../../Utilities/int2d.h"

typedef struct Renderable
{
	Texture* texture;
	int2d frame;
	float2d offset;
	float2d scale;
	void* data;
	void (*render)(SpriteBatch*, void*, Body*);
} Renderable;
