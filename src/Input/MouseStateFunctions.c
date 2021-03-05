#include <SDL2/SDL.h>
#include "MouseStateFunctions.h"

void MouseState_Create(MouseState* mouseState)
{
    memset(mouseState, 0, sizeof(MouseState));
    
    MouseButtons codes[3] = {
        MOUSEBUTTONS_LEFTCLICK,
        MOUSEBUTTONS_MIDDLECLICK,
        MOUSEBUTTONS_RIGHTCLICK,
    };
    memcpy(&mouseState->codes, &codes, sizeof(codes));
}

void MouseState_Update(ApplicationState* app, MouseState* mouseState)
{
    uint32_t currentMouseState = SDL_GetMouseState(&mouseState->positionReal.X, &mouseState->positionReal.Y);
    
    mouseState->position.X = (mouseState->positionReal.X - app->renderState.viewport.x) / app->renderState.windowZoom.X;
    mouseState->position.Y = (mouseState->positionReal.Y - app->renderState.viewport.y) / app->renderState.windowZoom.Y;
    
    bool isDown;
    
    for(int i = 1; i <= 3; i++)
    {
        isDown = currentMouseState & SDL_BUTTON(i);
        
        if(!isDown)
        {
            mouseState->down[i - 1] = fmin(0, mouseState->down[i - 1] - 1);
            
            continue;
        }
        
        mouseState->down[i - 1] = fmax(1, mouseState->down[i - 1] + 1);
    }
    
    for(int i = 0; i < app->renderState.targetsCount; i++)
    {
        app->renderState.targets[i].mouse = app->inputManager.mouseState.position;
        app->renderState.targets[i].mouse.X -= (app->renderState.targets[i].camera.resolution.X / 2) - app->renderState.targets[i].camera.position.X;
        app->renderState.targets[i].mouse.Y -= (app->renderState.targets[i].camera.resolution.Y / 2) - app->renderState.targets[i].camera.position.Y;
        
        app->renderState.targets[i].hovered = (
            app->inputManager.mouseState.position.X >= app->renderState.targets[i].position.X
            &&
            app->inputManager.mouseState.position.Y >= app->renderState.targets[i].position.Y
            &&
            app->inputManager.mouseState.position.X < app->renderState.targets[i].position.X + app->renderState.targets[i].camera.resolution.X
            &&
            app->inputManager.mouseState.position.Y < app->renderState.targets[i].position.Y + app->renderState.targets[i].camera.resolution.Y
        );
    }
}

int MouseState_GetIndex(MouseState* mouseState, MouseButtons mouseButton)
{
    for(int i = 0; i < sizeof(mouseState->codes) / sizeof(MouseButtons); i++)
    {
        if(mouseState->codes[i] == mouseButton)
        {
            return i;
        }
    }
    
    return -1;
}

int MouseState_GetButton(MouseState* mouseState, MouseButtons mouseButton)
{
    int i = MouseState_GetIndex(mouseState, mouseButton);
    
    if(i < 0 || i >= (sizeof(mouseState->down) / sizeof(MouseButtons)))
    {
        return 0;
    }
    
    return mouseState->down[i];
}

bool MouseState_Down(MouseState* mouseState, MouseButtons mouseButton)
{
    int b = MouseState_GetButton(mouseState, mouseButton);
    
    return b > 0;
}

bool MouseState_Up(MouseState* mouseState, MouseButtons mouseButton)
{
    int b = MouseState_GetButton(mouseState, mouseButton);
    
    return b <= 0;
}

bool MouseState_Pressed(MouseState* mouseState, MouseButtons mouseButton)
{
    int b = MouseState_GetButton(mouseState, mouseButton);
    
    return b == 1;
}

bool MouseState_Released(MouseState* mouseState, MouseButtons mouseButton)
{
    int b = MouseState_GetButton(mouseState, mouseButton);
    
    return b == -1;
}
