#include <flecs.h>
#include "Test1System.h"
#include "../../Application/ApplicationState.h"

void Test1System(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
	printf("Test1: %d\n", ++app->counter);
	
	if(app->counter >= 5)
	{
		app->quit = 1;
	}
}
