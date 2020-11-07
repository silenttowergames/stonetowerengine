#pragma once

#include "MouseButtons.h"
#include "../Utilities/float2d.h"
#include "../Utilities/int2d.h"

typedef struct MouseState
{
    float2d position;
    int2d positionReal;
    MouseButtons codes[3];
    int down[3];
} MouseState;
