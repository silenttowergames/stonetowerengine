#include "RenderStateFunctions.h"

RenderState RenderState_Init(int2d resolution)
{
    RenderState renderState;
    memset(&renderState, 0, sizeof(renderState));
    
    renderState.resolution = resolution;
    
    renderState.window = SDL_CreateWindow(
        "Testing",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280,
        720,
        FNA3D_PrepareWindowAttributes()
    ); // RenderState.window allocate
    
    return renderState;
}

void RenderState_Free(RenderState* renderState)
{
    SDL_DestroyWindow(renderState->window); // RenderState.window free
}
