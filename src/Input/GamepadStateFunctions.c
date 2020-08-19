#include <flecs.h>
#include "GamepadStateFunctions.h"

GamepadState GamepadState_Create(int index)
{
	GamepadState gamepadState;
	memset(&gamepadState, 0, sizeof(GamepadState));
	
	SDL_GameControllerButton buttons[15] = {
        SDL_CONTROLLER_BUTTON_A,
        SDL_CONTROLLER_BUTTON_B,
        SDL_CONTROLLER_BUTTON_X,
        SDL_CONTROLLER_BUTTON_Y,
        SDL_CONTROLLER_BUTTON_BACK,
        SDL_CONTROLLER_BUTTON_GUIDE,
        SDL_CONTROLLER_BUTTON_START,
        SDL_CONTROLLER_BUTTON_LEFTSTICK,
        SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        SDL_CONTROLLER_BUTTON_DPAD_UP,
        SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
    };
    memcpy(&gamepadState.buttons, buttons, sizeof(buttons));
	
	GamepadButtons codes[25] = {
		GPB_A,
		GPB_B,
		GPB_X,
		GPB_Y,
		GPB_BACK,
		GPB_GUIDE,
		GPB_START,
		GPB_STICK_LEFT,
		GPB_STICK_RIGHT,
		GPB_SHOULDER_LEFT,
		GPB_SHOULDER_RIGHT,
		GPB_DPAD_UP,
		GPB_DPAD_DOWN,
		GPB_DPAD_LEFT,
		GPB_DPAD_RIGHT,
		GPB_TRIGGER_LEFT,
		GPB_TRIGGER_RIGHT,
		GPB_STICK_LEFT_LEFT,
		GPB_STICK_LEFT_RIGHT,
		GPB_STICK_LEFT_DOWN,
		GPB_STICK_LEFT_UP,
		GPB_STICK_RIGHT_LEFT,
		GPB_STICK_RIGHT_RIGHT,
		GPB_STICK_RIGHT_DOWN,
		GPB_STICK_RIGHT_UP,
	};
	memcpy(&gamepadState.codes, codes, sizeof(codes));
	
	SDL_GameControllerAxis axes[6] = {
		SDL_CONTROLLER_AXIS_LEFTX,
		SDL_CONTROLLER_AXIS_LEFTY,
		SDL_CONTROLLER_AXIS_RIGHTX,
		SDL_CONTROLLER_AXIS_RIGHTY,
		SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
	};
	memcpy(&gamepadState.axes, axes, sizeof(axes));
	
	gamepadState.joystick = SDL_JoystickOpen(index);
	gamepadState.controller = SDL_GameControllerOpen(index);
	
	return gamepadState;
}

int GamepadState_GetIndexAxis(GamepadState* gamepadState, SDL_GameControllerAxis axis)
{
    for(int i = 0; i < sizeof(gamepadState->axes) / sizeof(SDL_GameControllerAxis); i++)
    {
        if(gamepadState->axes[i] == axis)
        {
            return i;
        }
    }
    
    return -1;
}

int GamepadState_GetIndexButton(GamepadState* gamepadState, SDL_GameControllerButton button)
{
    for(int i = 0; i < sizeof(gamepadState->buttons) / sizeof(SDL_GameControllerButton); i++)
    {
        if(gamepadState->buttons[i] == button)
        {
            return i;
        }
    }
    
    return -1;
}

void GamepadState_EventAxis(GamepadState* gamepadState, SDL_ControllerAxisEvent event)
{
    int i = GamepadState_GetIndexAxis(gamepadState, event.axis);
    
    if(i < 0)
    {
        return;
    }
    
    gamepadState->axesValues[i] = event.value;
}

void GamepadState_EventButton(GamepadState* gamepadState, SDL_ControllerButtonEvent event)
{
    int i = GamepadState_GetIndexButton(gamepadState, event.button);
    
    if (i < 0)
    {
        return;
    }
    
    switch (event.type)
    {
        case SDL_CONTROLLERBUTTONDOWN:
        {
            gamepadState->down[i] = fmin(5000, fmax(1, gamepadState->down[i] + 1));
        } break;
        
        case SDL_CONTROLLERBUTTONUP:
        {
            gamepadState->down[i] = -1;
        } break;
    }
}

void GamepadState_Update(GamepadState* gamepadState)
{
    for(int i = 0; i < sizeof(gamepadState->down) / sizeof(int); i++)
    {
        if(gamepadState->down[i] > 0)
        {
            gamepadState->down[i] = fmin(5000, fmax(1, gamepadState->down[i] + 1));
        }
        else
        {
            gamepadState->down[i] = fmax(-5000, fmin(-1, gamepadState->down[i] - 1));
        }
    }
}

int GamepadState_GetButton(GamepadState* gamepadState, GamepadButtons button)
{
    return gamepadState->down[button];
}

bool GamepadState_Down(GamepadState* gamepadState, GamepadButtons button)
{
    int state = GamepadState_GetButton(gamepadState, button);
    
    if(state > 0)
    {
        return true;
    }
    
    return false;
}
