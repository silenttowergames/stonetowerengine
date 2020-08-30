#pragma once

#include <flecs.h>
#include "../../Assets/Texture.h"
#include "../../Rendering/Camera.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/float2d.h"
#include "../../Utilities/int2d.h"

typedef struct Renderable
{
	Texture* texture;
	int2d frame;
	float2d offset;
	float2d scale;
	bool flipX;
	bool flipY;
	float rotation;
	void* data;
	void (*render)(SpriteBatch*, Camera*, void*, float2d);
	int layer;
	float depth;
	float parallax;
	uint32_t color;
} Renderable;
