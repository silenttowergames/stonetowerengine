#include <flecs.h>
#include "Test1System.h"
#include "../../Application/ApplicationState.h"

void initScene2(ecs_world_t* world)
{
	ECS_COMPONENT(world, int);
	ECS_COMPONENT(world, float);
    ecs_new(world, int);
	ecs_new(world, float);
}

void Test1System(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
	printf("Testasdfasdf1: %d\n", ++app->counter);
	
	if(app->counter >= 5)
	{
		app->flecsScene = initScene2;
	}
}
