#pragma once

#include <flecs.h>

void BasicAABBSystem(ecs_iter_t* it);
static void BasicAABBSystem_GetAllEntities();
static void BasicAABBSystem_Phase_Broad();
static void BasicAABBSystem_Phase_Narrow();
static void BasicAABB_TryHitboxes(
    BasicAABB* a0,
    Body* b0,
    Hitbox* hitbox0,
    BasicAABB* a1,
    Body* b1,
    Hitbox* hitbox1,
    bool isY
);
void BasicAABBSystemFree();
