#include "FlecsFunctions.h"
#include "FlecsMapFunctions.c"

ecs_world_t* Flecs_Init(ApplicationState* app)
{
	ecs_world_t* world = ecs_init();
	
	ecs_set_context(world, app);
	//ecs_set_target_fps(world, app->FPS);
	
	app->flecsInit(world);
	
	return world;
}

ecs_world_t* Flecs_Free(ecs_world_t* world)
{
	ecs_fini(world);
	
	return NULL;
}
