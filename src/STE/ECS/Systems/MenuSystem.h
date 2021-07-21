#pragma once

#include <flecs.h>

void MenuSystem(ecs_iter_t* it);

ECS_DTOR(Menu, ptr, {
    free(ptr->items); // MenuItem* free
})

#define MenuSystem_Init() ECS_SYSTEM(world, MenuSystem, EcsOnUpdate, Menu); ecs_set_component_actions(world, Menu, { .dtor = ecs_dtor(Menu), });
