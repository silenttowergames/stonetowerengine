#include <flecs.h>
#include "MoveSystem.h"
#include "../FlecsMapFunctions.h"
#include "../../Application/ApplicationState.h"
#include "../Components/AIPlayer.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"
#include "../../Audio/SoundFunctions.h"
#include "../../Application/ConfigFunctions.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"
#include "../../Utilities/wallsFunctions.h"
#include "../../GameData/GameDataAttribute.h"
#include "../../GameData/GameDataFunctions.h"

void MoveSystem(ecs_iter_t* it)
{
	fctx();
	
	if(keys(Pressed, t))
	{
		//printf("%d\n", gdValue("Integers", "hello", Int));
		//ecs_set_time_scale(it->world, 0);
		printf("test\n");
	}
	
	if(keys(Pressed, y))
	{
		//ecs_set_time_scale(it->world, 1);
		app->flecsScene = "map1";
	}
	
	if(keys(Pressed, u))
	{
		//ecs_set_time_scale(it->world, 2);
	}
	
	if(keys(Pressed, i))
	{
		//ecs_set_time_scale(it->world, 0.5f);
	}
	
	if(keys(Pressed, o))
	{
		//ecs_set_time_scale(it->world, 5);
	}
	
	if(keys(Pressed, p))
	{
		//ecs_set_time_scale(it->world, 0.125f);
	}
	
	AIPlayer* a = ecs_column(it, AIPlayer, 1);
	Body* b = ecs_column(it, Body, 2);
	
	for(int i = 0; i < it->count; i++)
	{
		memset(&b[i].velocity, 0, sizeof(float2d));
		
		if(keys(Down, RIGHT) || button(Down, 0, DPAD_RIGHT) || button(Down, 1, STICK_RIGHT_RIGHT) || axis(0, STICK_LEFT_DOWN) >= 0.9f)
		{
			b[i].velocity.X += a[i].speed * fdelta();
		}
		
		if(keys(Down, LEFT) || button(Down, 0, DPAD_LEFT) || button(Down, 0, STICK_RIGHT_LEFT) || button(Released, 0, STICK_LEFT_RIGHT))
		{
			b[i].velocity.X -= a[i].speed * fdelta();
		}
		
		if(keys(Down, DOWN) || button(Down, 0, DPAD_DOWN) || button(Down, 0, STICK_RIGHT_DOWN))
		{
			b[i].velocity.Y += a[i].speed * fdelta();
		}
		
		if(keys(Down, UP) || button(Down, 0, DPAD_UP) || button(Down, 0, STICK_RIGHT_UP))
		{
			b[i].velocity.Y -= a[i].speed * fdelta() * (keys(Down, LSHIFT) ? 0.0375f : 1);
		}
		
		if(button(Down, 0, X))
		{
			rumble(0, 1.0f, 500);
		}
	}
	
	if(
		(keys(Down, LALT) && keys(Pressed, RETURN))
		||
		(keys(Down, LCTRL) && keys(Pressed, f))
	)
	{
		if(app->config.fullscreen)
		{
			Config_Resize(app, 1280, 720, false);
		}
		else
		{
			Config_Resize(app, -1, -1, true);
		}
	}
	
	if(keys(Pressed, x))
	{
		//soundPlay("calm-example.ogg");
	}
	
	if(keys(Pressed, z))
	{
		//soundPlay("speech0");
	}
	
	if(keys(Pressed, c))
	{
		//soundPlay("hit.ogg");
	}
	
	if(keys(Pressed, v))
	{
		//app->flecsScene = "map1";
	}
	
	if(keys(Pressed, g))
	{
		//RenderState_VSync(app, true);
	}
	
	if(keys(Pressed, h))
	{
		//RenderState_VSync(app, false);
	}
}
