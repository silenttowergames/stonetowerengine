#pragma once

#include "RenderState.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY, RenderState_Zoom windowZoomType);
void RenderState_Free(RenderState* renderState);

void RenderState_InitRenderTargets(RenderState* renderState, int count);
void RenderState_AddRenderTarget(RenderState* renderState, RenderTarget renderTarget);
void RenderState_AddRenderTargets(RenderState* renderState, int count, ...);

#define renderTargets(l, ...) RenderState_InitRenderTargets(&app.renderState, l); RenderState_AddRenderTargets(&app.renderState, l, __VA_ARGS__)
