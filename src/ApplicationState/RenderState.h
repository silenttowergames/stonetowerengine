#pragma once

#include <SDL2/SDL.h>
#include <FNA3D.h>
#include "../Rendering/Camera.h"
#include "../Rendering/RenderTarget.h"
#include "../Rendering/SpriteBatch.h"
#include "../Utilities/Array.h"
#include "../Utilities/int2d.h"

typedef struct RenderState
{
    int2d resolution;
    int2d size;
    SDL_Window* window;
    const char* driver;
    int2d windowZoom;
    FNA3D_Device* device;
    FNA3D_Viewport viewport;
    int currentRenderTargetID;
    RenderTarget mainRenderTarget;
    Array targets;
    SpriteBatch spriteBatch;
    Shader shaderSpriteEffect;
    Camera camera;
    FNA3D_Buffer* vertexBuffer;
    FNA3D_VertexBufferBinding vertexBufferBinding;
} RenderState;
