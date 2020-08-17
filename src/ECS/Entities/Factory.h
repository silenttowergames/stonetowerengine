#pragma once

#include <flecs.h>

typedef struct Factory
{
	const char* key;
	void (*callable)(ecs_world_t*, float, float, int);
} Factory;
