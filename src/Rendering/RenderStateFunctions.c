#include <FNA3D.h>
#include <SDL2/SDL.h>
#include "RenderStateFunctions.h"

RenderState RenderState_New()
{
	RenderState renderState;
	memset(&renderState, 0, sizeof(RenderState));
	
	renderState.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, FNA3D_PrepareWindowAttributes()); // RenderState.window allocate
	
	return renderState;
}

void RenderState_Free(RenderState renderState)
{
	SDL_DestroyWindow(renderState.window);
}
