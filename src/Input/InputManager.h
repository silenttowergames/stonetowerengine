#pragma once

#include "GamepadState.h"
#include "KeyboardState.h"
#include "MouseState.h"

typedef struct InputManager
{
	KeyboardState keyboardState;
	GamepadState gamepadStates[8];
	MouseState mouseState;
} InputManager;
