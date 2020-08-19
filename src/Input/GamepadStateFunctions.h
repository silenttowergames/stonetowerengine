#pragma once

#include "GamepadState.h"

GamepadState GamepadState_Create();
int GamepadState_GetIndexAxis(GamepadState* gamepadState, SDL_GameControllerAxis axis);
int GamepadState_GetIndexButton(GamepadState* gamepadState, SDL_GameControllerButton button);
void GamepadState_EventAxis(GamepadState* gamepadState, SDL_ControllerAxisEvent event);
void GamepadState_EventButton(GamepadState* gamepadState, SDL_ControllerButtonEvent event);
void GamepadState_Update(GamepadState* gamepadState);
int GamepadState_GetButton(GamepadState* gamepadState, GamepadButtons button);
bool GamepadState_Down(GamepadState* gamepadState, GamepadButtons button);

#define button(state, index, button) GamepadState_##state(&app->inputManager.gamepadStates[index], GPB_##button)
