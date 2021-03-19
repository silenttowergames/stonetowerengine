#include <flecs.h>
#include "EngineUpdateSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Audio/AudioManagerFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"
#include "../../Input/MouseStateFunctions.h"

void EngineUpdateSystem(ecs_iter_t* it)
{
	fctx();
	
	AudioManager_update(app);
	
	KeyboardState_Update(&app->inputManager.keyboardState);
	MouseState_Update(app, &app->inputManager.mouseState);
	
	for(int i = 0; i < sizeof(app->inputManager.gamepadStates) / sizeof(GamepadState); i++)
	{
		GamepadState_Update(&app->inputManager.gamepadStates[i]);
	}
}
