#pragma once

#include "RenderState.h"

RenderState RenderState_New();
// FIXME: RenderState_Free param needs to be changed. We're going with "always use a pointer to a state var"
void RenderState_Free(RenderState renderState);
