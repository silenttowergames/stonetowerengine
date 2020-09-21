#include "FlecsFunctions.h"

ecs_world_t* Flecs_Init(ApplicationState* app)
{
	ecs_world_t* world = ecs_init();
	
	ecs_set_context(world, app);
	ecs_set_target_fps(world, app->FPS);
	
	app->flecsInit(world);
	
	return world;
}

ecs_world_t* Flecs_Free(ecs_world_t* world)
{
	ecs_fini(world);
	
	return NULL;
}

uint64_t Flecs_Map_Key(const char* key)
{
	return hashlittle(key, strlen(key), 0);
	
	/*
	uint32_t a, b;
	hashlittle2(key, strlen(key), &a, &b);
	uint64_t db = b;
	
	return a + (db << 32);
	//*/
}
