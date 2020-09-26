#pragma once

#include "RenderTarget.h"

#define RENDERTARGET_MAIN -1
#define RENDERTARGET_NONE -2

RenderTarget RenderTarget_Create(ApplicationState* app, int2d resolution, int2d position, bool scale, FNA3D_Vec4 backgroundColor);
void RenderTarget_Start(ApplicationState* app, int renderTargetID);
void RenderTarget_Stop(ApplicationState* app);
void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device);
