#pragma once

#include <flecs.h>

void MenuSystem(ecs_iter_t* it);

#define MenuSystem_Init() ECS_SYSTEM(world, MenuSystem, EcsOnUpdate, Menu, :MenuItem); ecs_set_component_actions(world, Menu, { .dtor = ecs_dtor(Menu), });
