#pragma once

#include <stdlib.h>
#include "../includes_vendor.h"

#include "Texture.h"
#include "../Application/ApplicationState.h"
#include "../ECS/Components/Renderable.h"

typedef struct FontStashFNA3D
{
    ApplicationState* app;
    Texture texture;
    Renderable* renderable;
    int font;
} FontStashFNA3D;
