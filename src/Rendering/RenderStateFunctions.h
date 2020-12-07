#pragma once

#include <flecs.h>
#include "RenderState.h"
#include "../includes_libs.h"
#include "../Application/ApplicationState.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY, RenderState_Zoom windowZoomType);
void RenderState_Free(RenderState* renderState);

void RenderState_InitRenderTargets(RenderState* renderState, int count);
void RenderState_AddRenderTarget(RenderState* renderState, RenderTarget renderTarget);
void RenderState_AddRenderTargets(RenderState* renderState, int count, ...);

void RenderState_Resize(ApplicationState* app, int sizeX, int sizeY);

void RenderState_VSync(RenderState* renderState, bool enabled);

#define renderTargets(l, ...) RenderState_InitRenderTargets(&app.renderState, l); RenderState_AddRenderTargets(&app.renderState, l, __VA_ARGS__)
