#pragma once

#include <flecs.h>
#include "Factory.h"

Factory Factory_Create(const char* key, void (*callable)(ecs_world_t*, float, float));
