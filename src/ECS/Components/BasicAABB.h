#pragma once

#include "HitboxFunctions.h"

typedef struct BasicAABB
{
    int hitboxesCount;
    Hitbox* hitboxes;
} BasicAABB;

#define BasicAABB_Create(length, ...) { length, Hitbox_CreateList(length, __VA_ARGS__), }
