#pragma once

#include "Hitbox.h"

Hitbox Hitbox_CreateBasic(float2d size);
Hitbox Hitbox_CreateSquare(float size);

Hitbox* Hitbox_CreateList(int length, ...);
