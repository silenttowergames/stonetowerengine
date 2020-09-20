#pragma once

#include "RenderTarget.h"

RenderTarget RenderTarget_Create(FNA3D_Device* device, int2d size, int2d resolution, int2d position);
void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device);
