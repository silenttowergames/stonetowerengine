#pragma once

#include "GamepadState.h"
#include "KeyboardState.h"

typedef struct InputManager
{
	KeyboardState keyboardState;
	GamepadState gamepadStates[8];
} InputManager;
