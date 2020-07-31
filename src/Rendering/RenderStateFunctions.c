#include <FNA3D.h>
#include <SDL2/SDL.h>
#include "RenderStateFunctions.h"

RenderState RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY)
{
	RenderState renderState;
	memset(&renderState, 0, sizeof(RenderState));
	
	renderState.size.X = sizeX;
	renderState.size.Y = sizeY;
	
	renderState.resolution.X = resX;
	renderState.resolution.Y = resY;
	
	renderState.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, FNA3D_PrepareWindowAttributes()); // RenderState.window allocate
	
	FNA3D_PresentationParameters presentationParameters;
	memset(&presentationParameters, 0, sizeof(presentationParameters));
	presentationParameters.backBufferWidth = renderState.size.X;
	presentationParameters.backBufferHeight = renderState.size.Y;
	presentationParameters.deviceWindowHandle = renderState.window;
	presentationParameters.backBufferFormat = FNA3D_SURFACEFORMAT_COLOR;
	renderState.presentationParameters = presentationParameters;
	
	FNA3D_Viewport viewport;
	memset(&viewport, 0, sizeof(FNA3D_Viewport));
	viewport.w = sizeX;
	viewport.h = sizeY;
	renderState.viewport = viewport;
	
	renderState.camera.resolution.X = resX;
	renderState.camera.resolution.Y = resY;
	
	renderState.device = FNA3D_CreateDevice(&renderState.presentationParameters, STE_DEBUG);
	
	return renderState;
}

void RenderState_Free(RenderState* renderState)
{
	SDL_DestroyWindow(renderState->window); // RenderState.window free
}
