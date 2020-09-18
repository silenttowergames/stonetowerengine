#pragma once

#include"RenderTarget.h"

void RenderTarget_Create(FNA3D_Device* device, int2d size, int2d position);
void RenderTarget_Destroy(RenderTarget* renderTarget, FNA3D_Device* device);
