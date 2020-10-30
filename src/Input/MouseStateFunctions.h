#pragma once

#include "MouseState.h"

void MouseState_Create(MouseState* mouseState);
void MouseState_Update(ApplicationState* app, MouseState* mouseState);
int MouseState_GetIndex(MouseState* mouseState, MouseButtons mouseButton);
int MouseState_GetButton(MouseState* mouseState, MouseButtons mouseButton);
bool MouseState_Down(MouseState* mouseState, MouseButtons mouseButton);
bool MouseState_Up(MouseState* mouseState, MouseButtons mouseButton);
bool MouseState_Pressed(MouseState* mouseState, MouseButtons mouseButton);
bool MouseState_Released(MouseState* mouseState, MouseButtons mouseButton);

#define mouse(state, button) MouseState_##state(&app->inputManager.mouseState, MBs_##button)
