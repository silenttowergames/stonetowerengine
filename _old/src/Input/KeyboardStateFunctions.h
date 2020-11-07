#pragma once

#include "KeyboardState.h"

void KeyboardState_Create(KeyboardState* keyboardState);

int KeyboardState_GetKey(KeyboardState* keyboardState, SDL_Keycode key);
int KeyboardState_GetIndex(KeyboardState* keyboardState, SDL_Keycode key);

void KeyboardState_Event(KeyboardState* keyboardState, SDL_KeyboardEvent key);
void KeyboardState_Update(KeyboardState* keyboardState);
void KeyboardState_EndUpdate(KeyboardState* keyboardState);

bool KeyboardState_Down(KeyboardState* keyboardState, SDL_Keycode key);
bool KeyboardState_Up(KeyboardState* keyboardState, SDL_Keycode key);
bool KeyboardState_Pressed(KeyboardState* keyboardState, SDL_Keycode key);
bool KeyboardState_Released(KeyboardState* keyboardState, SDL_Keycode key);
bool KeyboardState_Held(KeyboardState* keyboardState, SDL_Keycode key);

void KeyboardState_Type(KeyboardState* keyboardState, char character);

#define key(state, key) KeyboardState_##state(&app->inputManager.keyboardState, SDLK_##key)
