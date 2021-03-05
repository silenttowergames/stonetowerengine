#pragma once

#define STE_ECS_COMPONENT_DECLARE(w, T) ECS_COMPONENT_DECLARE(T)
#define STE_ECS_COMPONENT_DEFINE(w, T) ECS_COMPONENT_DEFINE(w, T)

#define ECS_Setup(de, w) \
    STE_ECS_COMPONENT_ ## de(w, AINPC);\
    STE_ECS_COMPONENT_ ## de(w, AIPlayer);\
    STE_ECS_COMPONENT_ ## de(w, Animate);\
    STE_ECS_COMPONENT_ ## de(w, BasicAABB);\
    STE_ECS_COMPONENT_ ## de(w, Body);\
    STE_ECS_COMPONENT_ ## de(w, CameraFollow);\
    STE_ECS_COMPONENT_ ## de(w, Menu);\
    STE_ECS_COMPONENT_ ## de(w, MenuItem);\
    STE_ECS_COMPONENT_ ## de(w, PauseMenu);\
    STE_ECS_COMPONENT_ ## de(w, Renderable);\
    STE_ECS_COMPONENT_ ## de(w, TiledObject);\
    STE_ECS_COMPONENT_ ## de(w, TileLayerCollides);

ECS_Setup(DECLARE, )
