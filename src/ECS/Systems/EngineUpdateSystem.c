#include <flecs.h>
#include "EngineUpdateSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"

void EngineUpdateSystem(ecs_iter_t* it)
{
	fctx();
	
	KeyboardState_Update(&app->inputManager.keyboardState);
	
	for(int i = 0; i < sizeof(app->inputManager.gamepadStates) / sizeof(GamepadState); i++)
	{
		GamepadState_Update(&app->inputManager.gamepadStates[i]);
	}
}