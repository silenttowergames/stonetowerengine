#pragma once

#include <flecs.h>
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/HitboxFunctions.h"
#include "../Components/Renderable.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/walls.h"

void BasicAABBSystem(ecs_iter_t* it);
static void BasicAABBSystem_FindSolidMapLayer();
static void BasicAABBSystem_GetAllEntities();
static void BasicAABBSystem_Phase_Broad();
static void BasicAABBSystem_Phase_Narrow();
static void BasicAABB_TryHitboxes(
    BasicAABB* a0,
    Body* b0,
    Hitbox* hitbox0,
    walls* w0,
    BasicAABB* a1,
    Body* b1,
    Hitbox* hitbox1,
    walls* w1,
    bool isY
);
void BasicAABBSystemFree();
