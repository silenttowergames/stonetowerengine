#pragma once

#include <FNA3D.h>
#include "../Assets/Shader.h"
#include "../Rendering/Camera.h"
#include "../Utilities/int2d.h"

typedef struct RenderTarget
{
	FNA3D_RenderTargetBinding binding;
	FNA3D_Viewport viewport;
	Camera camera;
	int2d size;
	int2d position;
	Shader* shaders;
} RenderTarget;
