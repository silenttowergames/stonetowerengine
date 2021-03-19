#pragma once

#include <flecs.h>
#include "../../Assets/TiledJSONObject.h"

typedef struct Factory
{
	const char* key;
	ecs_entity_t (*callable)(ecs_world_t*, float, float, int, TiledJSONObject*);
} Factory;
