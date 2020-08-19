#include <flecs.h>
#include "MoveSystem.h"
#include "../Components/AIPlayer.h"
#include "../Components/Body.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		if(key(Down, RIGHT) || button(Down, 0, DPAD_RIGHT) || button(Down, 1, STICK_RIGHT_RIGHT) || axis(0, STICK_LEFT_DOWN) >= 0.9f)
		{
			b[i].position.X += a[i].speed;
		}
		
		if(key(Down, LEFT) || button(Down, 0, DPAD_LEFT) || button(Down, 0, STICK_RIGHT_LEFT) || button(Released, 0, STICK_LEFT_RIGHT))
		{
			b[i].position.X -= a[i].speed;
		}
		
		if(key(Down, DOWN) || button(Down, 0, DPAD_DOWN) || button(Down, 0, STICK_RIGHT_DOWN))
		{
			b[i].position.Y += a[i].speed;
		}
		
		if(key(Down, UP) || button(Down, 0, DPAD_UP) || button(Down, 0, STICK_RIGHT_UP))
		{
			b[i].position.Y -= a[i].speed;
		}
	}
}
