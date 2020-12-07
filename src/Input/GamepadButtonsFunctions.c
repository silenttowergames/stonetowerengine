#include "GamepadButtonsFunctions.h"

GamepadButtons GamepadButton_FromSDLButton(SDL_GameControllerButton button)
{
    switch(button)
    {
        case SDL_CONTROLLER_BUTTON_A: return GPB_A;
        case SDL_CONTROLLER_BUTTON_B: return GPB_B;
        case SDL_CONTROLLER_BUTTON_X: return GPB_X;
        case SDL_CONTROLLER_BUTTON_Y: return GPB_Y;
        case SDL_CONTROLLER_BUTTON_BACK: return GPB_BACK;
        case SDL_CONTROLLER_BUTTON_GUIDE: return GPB_GUIDE;
        case SDL_CONTROLLER_BUTTON_START: return GPB_START;
        case SDL_CONTROLLER_BUTTON_LEFTSTICK: return GPB_STICK_LEFT;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return GPB_STICK_RIGHT;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return GPB_SHOULDER_LEFT;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return GPB_SHOULDER_RIGHT;
        case SDL_CONTROLLER_BUTTON_DPAD_UP: return GPB_DPAD_UP;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return GPB_DPAD_DOWN;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return GPB_DPAD_LEFT;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return GPB_DPAD_RIGHT;
    }
    
    return GPB_INVALID;
}

SDL_GameControllerAxis GamepadButton_ToSDLAxis(GamepadButtons axis)
{
    switch(axis)
    {
        case GPB_TRIGGER_LEFT: return SDL_CONTROLLER_AXIS_TRIGGERLEFT;
        case GPB_TRIGGER_RIGHT: return SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
        case GPB_STICK_LEFT_LEFT:
        case GPB_STICK_LEFT_RIGHT:
        {
            return SDL_CONTROLLER_AXIS_LEFTX;
        }
        case GPB_STICK_LEFT_DOWN:
        case GPB_STICK_LEFT_UP:
        {
            return SDL_CONTROLLER_AXIS_LEFTY;
        }
        case GPB_STICK_RIGHT_LEFT:
        case GPB_STICK_RIGHT_RIGHT:
        {
            return SDL_CONTROLLER_AXIS_RIGHTX;
        }
        case GPB_STICK_RIGHT_DOWN:
        case GPB_STICK_RIGHT_UP:
        {
            return SDL_CONTROLLER_AXIS_RIGHTY;
        }
    }
    
    return SDL_CONTROLLER_AXIS_INVALID;
}
