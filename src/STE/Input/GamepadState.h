#pragma once

#include <SDL2/SDL.h>
#include "GamepadButtons.h"

typedef struct GamepadState
{
    SDL_Joystick* joystick;
    SDL_GameController* controller;
    SDL_GameControllerButton buttons[15];
    GamepadButtons codes[25];
    int down[25];
    SDL_GameControllerAxis axes[6];
    int axesValues[6];
    int instance;
    SDL_Haptic* haptic;
    const char* name;
    Uint16 vendor;
    Uint16 product;
    SDL_JoystickGUID guid;
} GamepadState;
