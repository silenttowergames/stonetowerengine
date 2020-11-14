#pragma once

#include "RenderState.h"

RenderState RenderState_Init(int2d resolution);
void RenderState_Free(RenderState* renderState);
