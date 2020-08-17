#include <flecs.h>
#include "MoveSystem.h"
#include "../Components/AIPlayer.h"
#include "../Components/Body.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void MoveSystem(ecs_iter_t* it)
{
	ecs_world_t* world = it->world;
	
	ctx();
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		if(key(Down, RIGHT))
		{
			b[i].position.X += a[i].speed;
		}
	}
}
