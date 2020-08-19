#include <flecs.h>
#include "MoveSystem.h"
#include "../Components/AIPlayer.h"
#include "../Components/Body.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		if(key(Down, RIGHT) || button(Down, 0, DPAD_RIGHT))
		{
			b[i].position.X += a[i].speed;
		}
		
		if(key(Down, LEFT) || button(Down, 0, DPAD_LEFT))
		{
			b[i].position.X -= a[i].speed;
		}
		
		if(key(Down, DOWN) || button(Down, 0, DPAD_DOWN))
		{
			b[i].position.Y += a[i].speed;
		}
		
		if(key(Down, UP) || button(Down, 0, DPAD_UP))
		{
			b[i].position.Y -= a[i].speed;
		}
	}
}
