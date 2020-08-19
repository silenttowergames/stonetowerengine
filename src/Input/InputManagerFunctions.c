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
		inputManager.gamepadStates[i] = GamepadState_Create(i);
	}
	
	return inputManager;
}

void InputManager_GamepadEventButton(InputManager* inputManager, SDL_ControllerButtonEvent event)
{
	int index = event.which;
	
	if(index < 0 || index >= (sizeof(inputManager->gamepadStates) / sizeof(GamepadState)))
	{
		return;
	}
	
	GamepadState_EventButton(&inputManager->gamepadStates[index], event);
}

void InputManager_GamepadEventAxis(InputManager* inputManager, SDL_ControllerAxisEvent event)
{
	int index = event.which;
	
	if(index < 0 || index >= (sizeof(inputManager->gamepadStates) / sizeof(GamepadState)))
	{
		return;
	}
	
	GamepadState_EventAxis(&inputManager->gamepadStates[index], event);
}
