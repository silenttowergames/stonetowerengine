#pragma once

#ifndef FONTSTASH_IMPLEMENTATION
#define FONTSTASH_IMPLEMENTATION
#include "../vendor/fontstash/fontstash.h"
#endif

#include "../Application/ApplicationState.h"
#include "Texture.h"

typedef struct FontStashFNA3D
{
    ApplicationState* app;
    Texture texture;
    float2d (*renderOffset)(int, int);
    int duration;
} FontStashFNA3D;
