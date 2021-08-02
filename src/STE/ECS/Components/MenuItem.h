#pragma once

#include "Menu.h"
#include "Renderable.h"
#include "../../Application/ApplicationState.h"

typedef struct MenuItem
{
    ecs_entity_t menu;
    void (*select)(ApplicationState*, ecs_world_t*, ecs_entity_t, Menu*);
    void (*hovering)(ApplicationState*, ecs_world_t*, ecs_entity_t, Menu*, bool);
} MenuItem;
