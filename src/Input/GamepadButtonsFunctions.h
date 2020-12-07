#pragma once

#include <SDL2/SDL.h>
#include "GamepadButtons.h"

GamepadButtons GamepadButton_FromSDLButton(SDL_GameControllerButton button);
SDL_GameControllerAxis GamepadButton_ToSDLAxis(GamepadButtons axis);
