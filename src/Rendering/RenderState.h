#pragma once

#include <SDL2/SDL.h>
#include <FNA3D.h>
#include "Camera.h"
#include "SpriteBatch.h"
#include "../Assets/Shader.h"
#include "../Rendering/RenderTarget.h"
#include "../Utilities/int2d.h"

typedef struct RenderState
{
	char* windowTitle;
	SDL_Window* window;
	FNA3D_Device* device;
	FNA3D_PresentationParameters presentationParameters;
	FNA3D_Viewport viewport;
	int2d resolution;
	int2d size;
	Camera camera;
	Shader shaderSpriteEffect;
	SpriteBatch spriteBatch;
	FNA3D_Buffer* vertexBuffer;
	FNA3D_VertexBufferBinding vertexBufferBinding;
	FNA3D_VertexElement vertexElements[3];
	ecs_query_t* sortQuery;
	RenderTarget mainRenderTarget;
	RenderTarget* targets;
	int targetsCount;
	int targetsCountSoFar;
} RenderState;
