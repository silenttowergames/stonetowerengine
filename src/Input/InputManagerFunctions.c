#include "InputManagerFunctions.h"
#include "KeyboardStateFunctions.h"

InputManager InputManager_Create()
{
	InputManager inputManager;
	memset(&inputManager, 0, sizeof(InputManager));
	
	KeyboardState_Create(&inputManager.keyboardState);
	
	return inputManager;
}
