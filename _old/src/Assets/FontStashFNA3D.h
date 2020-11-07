#pragma once

#ifndef FONTSTASH_IMPLEMENTATION
#define FONTSTASH_IMPLEMENTATION
#include "../vendor/fontstash/fontstash.h"
#endif

#include "Texture.h"
#include "../Application/ApplicationState.h"
#include "../ECS/Components/Renderable.h"

typedef struct FontStashFNA3D
{
    ApplicationState* app;
    Texture texture;
    Renderable* renderable;
} FontStashFNA3D;
