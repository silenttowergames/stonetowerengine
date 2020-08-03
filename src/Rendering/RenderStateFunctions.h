#pragma once

#include "RenderState.h"

void RenderState_New(ApplicationState* app, int sizeX, int sizeY, int resX, int resY);
void RenderState_Free(RenderState* renderState);
