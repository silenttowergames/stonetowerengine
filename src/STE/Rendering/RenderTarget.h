#pragma once

#include <FNA3D.h>
#include "../Assets/Shader.h"
#include "../Assets/Texture.h"
#include "../Rendering/Camera.h"
#include "../Utilities/float2d.h"
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
	FNA3D_Vec4 backgroundColor;
	bool scale;
	float2d mouse;
	bool hovered;
	int2d drawResolution;
} RenderTarget;
