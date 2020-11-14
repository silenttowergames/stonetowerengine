#pragma once

#include "RenderState.h"

;
#include <FNA3D.h>
#include <SDL2/SDL.h>
#include "CameraFunctions.h"
#include "RenderStateFunctions.h"
#include "RenderTargetFunctions.h"
#include "SpriteBatchFunctions.h"
#include "../Application/ApplicationState.h"
#include "../Assets/ShaderFunctions.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY, RenderState_Zoom windowZoomType)
void RenderState_Free(RenderState* renderState);
void RenderState_InitRenderTargets(RenderState* renderState, int count);
void RenderState_AddRenderTarget(RenderState* renderState, RenderTarget renderTarget);
void RenderState_AddRenderTargets(RenderState* renderState, int count, ...);
void RenderState_Resize(ApplicationState* app, int sizeX, int sizeY);
;
