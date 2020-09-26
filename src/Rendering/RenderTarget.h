#pragma once

#include <FNA3D.h>
#include "../Assets/Shader.h"
#include "../Assets/Texture.h"
#include "../Rendering/Camera.h"
#include "../Utilities/int2d.h"

typedef struct RenderTarget
{
	FNA3D_RenderTargetBinding binding;
	FNA3D_Viewport viewport;
	Camera camera;
	int2d size;
	int2d position;
	Shader** shaders;
	int shadersCount;
	Texture texture;
	uint32_t backgroundColor;
	bool scale;
} RenderTarget;
