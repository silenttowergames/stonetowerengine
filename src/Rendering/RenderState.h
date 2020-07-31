#pragma once

#include <SDL2/SDL.h>
#include <FNA3D.h>
#include "../Utilities/int2d.h"
#include "Camera.h"

typedef struct RenderState
{
	SDL_Window* window;
	FNA3D_Device* device;
	FNA3D_PresentationParameters presentationParameters;
	FNA3D_Viewport viewport;
	int2d resolution;
	int2d size;
	Camera camera;
} RenderState;
