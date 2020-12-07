#pragma once

#include <flecs.h>
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../Components/HitboxFunctions.h"
#include "../Components/Renderable.h"
#include "../../Rendering/SpriteBatch.h"
#include "../../Utilities/walls.h"

#define BasicAABBSystem_Init()\
    ECS_COMPONENT(world, BasicAABB);\
    ecs_set_component_actions(world, BasicAABB, { .dtor = ecs_dtor(BasicAABB), });\
    ECS_SYSTEM(world, BasicAABBSystem, EcsOnUpdate, 0);\
    aabbQuery = ecs_query_new(world, "BasicAABB, Body");\
    aabbMapQuery = ecs_query_new(world, "TileLayerCollides, Renderable, Body");

ecs_query_t* aabbQuery = NULL;
ecs_query_t* aabbMapQuery = NULL;
static ecs_entity_t* aabbEnitities = NULL;
static BasicAABB** aabbBasics = NULL;
static Body** aabbBodies = NULL;
static ecs_map_t* aabbHashTable = NULL;
static int entitiesCount;
static Renderable* tileMapSolid = NULL;
static Body* tileMapSolidBody = NULL;

void BasicAABBSystem(ecs_iter_t* it);
static void BasicAABBSystem_FindSolidMapLayer();
static void BasicAABBSystem_GetAllEntities();
static void BasicAABBSystem_Phase_Broad();
static void BasicAABBSystem_Phase_Narrow();
static void BasicAABBSystem_Entity_Tilemap(walls wall, BasicAABB* aabb, int h0, Body* body, Renderable* tileMapSolid, Body* tileMapSolidBody, bool isY);
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
