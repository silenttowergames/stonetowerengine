#pragma once

#include "Hitbox.h"
#include "../../Utilities/walls.h"

Hitbox Hitbox_CreateBasic(float2d size);
Hitbox Hitbox_CreateSquare(float size);

Hitbox* Hitbox_CreateList(int length, ...);

walls Hitbox_GetWalls(Hitbox* hitbox, float2d position);
