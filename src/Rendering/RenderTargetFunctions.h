#pragma once

#include "RenderTarget.h"

#define RENDERTARGET_MAIN -1
#define RENDERTARGET_NONE -2

RenderTarget RenderTarget_Create(FNA3D_Device* device, int2d size, int2d resolution, int2d position);
void RenderTarget_Start(ApplicationState* app, int renderTargetID);
void RenderTarget_Stop(ApplicationState* app);
void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device);
