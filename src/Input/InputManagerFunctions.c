#include "InputManagerFunctions.h"
#include "GamepadStateFunctions.h"
#include "KeyboardStateFunctions.h"

InputManager InputManager_Create()
{
	InputManager inputManager;
	memset(&inputManager, 0, sizeof(InputManager));
	
	KeyboardState_Create(&inputManager.keyboardState);
	
	for(int i = 0; i < sizeof(inputManager.gamepadStates) / sizeof(GamepadState); i++)
	{
		inputManager.gamepadStates[i] = GamepadState_Create(-1);
	}
	
	return inputManager;
}

void InputManager_GamepadEventButton(InputManager* inputManager, SDL_ControllerButtonEvent event)
{
	int count = sizeof(inputManager->gamepadStates) / sizeof(GamepadState);
	int index = event.which;
	
	for(int i = 0; i < count; i++)
	{
		if(inputManager->gamepadStates[i].instance != index)
		{
			continue;
		}
		
		GamepadState_EventButton(&inputManager->gamepadStates[i], event);
	}
}

void InputManager_GamepadEventAxis(InputManager* inputManager, SDL_ControllerAxisEvent event)
{
	int count = sizeof(inputManager->gamepadStates) / sizeof(GamepadState);
	int index = event.which;
	
	for(int i = 0; i < count; i++)
	{
		if(inputManager->gamepadStates[i].instance != index)
		{
			continue;
		}
		
		GamepadState_EventAxis(&inputManager->gamepadStates[i], event);
	}
}
