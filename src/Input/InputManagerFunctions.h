#pragma once

#include"InputManager.h"

InputManager InputManager_Create();
void InputManager_GamepadEventButton(InputManager* inputManager, SDL_ControllerButtonEvent event);
void InputManager_GamepadEventAxis(InputManager* inputManager, SDL_ControllerAxisEvent event);
