#pragma once

#include "GamepadState.h"
#include "GamepadButtonsFunctions.h"

GamepadState GamepadState_Create(int index);
void GamepadState_Close(GamepadState* gamepadState);
int GamepadState_GetIndexAxis(GamepadState* gamepadState, SDL_GameControllerAxis axis);
int GamepadState_GetIndexButton(GamepadState* gamepadState, SDL_GameControllerButton button);
void GamepadState_EventAxis(GamepadState* gamepadState, SDL_ControllerAxisEvent event);
void GamepadState_EventButton(GamepadState* gamepadState, SDL_ControllerButtonEvent event);
void GamepadState_UpdateAxis(GamepadState* gamepadState, GamepadButtons button, bool positive);
void GamepadState_UpdateAxes(GamepadState* gamepadState);
void GamepadState_Update(GamepadState* gamepadState);
int GamepadState_GetButton(GamepadState* gamepadState, GamepadButtons button);
bool GamepadState_Down(GamepadState* gamepadState, GamepadButtons button);
bool GamepadState_Up(GamepadState* gamepadState, GamepadButtons button);
bool GamepadState_Pressed(GamepadState* gamepadState, GamepadButtons button);
bool GamepadState_Released(GamepadState* gamepadState, GamepadButtons button);
int GamepadState_Axis(GamepadState* gamepadState, SDL_GameControllerAxis axis);
float GamepadState_AxisF(GamepadState* gamepadState, SDL_GameControllerAxis axis);

#define button(state, index, button) GamepadState_##state(&app->inputManager.gamepadStates[index], GPB_##button)
#define axis(index, axis) GamepadState_AxisF(&app->inputManager.gamepadStates[index], GamepadButton_ToSDLAxis(GPB_##axis))
#define rumble(index, strength0, strength1, duration) {\
    if(app->inputManager.gamepadStates[index].haptic != NULL)\
    {\
        SDL_HapticRumblePlay(app->inputManager.gamepadStates[index].haptic, 1.0f / ((float)0xFFFF / (float)strength0), duration);\
    }\
    else\
    {\
        SDL_JoystickRumble(app->inputManager.gamepadStates[index].joystick, strength0, strength1, duration);\
    }\
}
