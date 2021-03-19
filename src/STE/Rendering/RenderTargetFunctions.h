#pragma once

#include <flecs.h>
#include "RenderTarget.h"
#include "../Application/ApplicationState.h"
#include "../Assets/TextureFunctions.h"
#include "../Utilities/colorFunctions.h"

#define RENDERTARGET_MAIN -1
#define RENDERTARGET_NONE -2
#define RENDERTARGET_WINDOW -3
#define RENDERTARGET_CLOSED -4

RenderTarget RenderTarget_Create(ApplicationState* app, int2d resolution, int2d position, bool scale, FNA3D_Vec4 backgroundColor);
RenderTarget RenderTarget_Refresh(ApplicationState* app, RenderTarget* renderTarget);
void RenderTarget_Start(ApplicationState* app, int renderTargetID);
void RenderTarget_Stop(ApplicationState* app);
void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device);
