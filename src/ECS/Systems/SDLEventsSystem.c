#include <SDL2/SDL.h>
#include <flecs.h>
#include "SDLEventsSystem.h"
#include "../../Application/ApplicationStateFunctions.h"
#include "../../Input/GamepadStateFunctions.h"
#include "../../Input/InputManagerFunctions.h"
#include "../../Input/KeyboardStateFunctions.h"

static const char button_map[256] = {
  [ SDL_BUTTON_LEFT   & 0xff ] =  MU_MOUSE_LEFT,
  [ SDL_BUTTON_RIGHT  & 0xff ] =  MU_MOUSE_RIGHT,
  [ SDL_BUTTON_MIDDLE & 0xff ] =  MU_MOUSE_MIDDLE,
};
static const char key_map[256] = {
  [ SDLK_LSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_RSHIFT       & 0xff ] = MU_KEY_SHIFT,
  [ SDLK_LCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_RCTRL        & 0xff ] = MU_KEY_CTRL,
  [ SDLK_LALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RALT         & 0xff ] = MU_KEY_ALT,
  [ SDLK_RETURN       & 0xff ] = MU_KEY_RETURN,
  [ SDLK_BACKSPACE    & 0xff ] = MU_KEY_BACKSPACE,
};

void SDLEventsSystem(ApplicationState* app)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				app->quit = true;
				
				break;
			}
			
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					{
						AudioManager_focus(&app->assetManager);
						
						app->focused = true;
						
						break;
					}
					
					case SDL_WINDOWEVENT_FOCUS_LOST:
					{
						AudioManager_blur(&app->assetManager);
						
						app->focused = false;
						
						break;
					}
				}
			} break;
			
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				int c = key_map[event.key.keysym.sym & 0xff];
				if(c && event.type == SDL_KEYDOWN)
				{
					mu_input_keydown(app->mui, c);
				}
				else if(c && event.type == SDL_KEYUP)
				{
					mu_input_keyup(app->mui, c);
				}
				
				KeyboardState_Event(&app->inputManager.keyboardState, event.key);
			} break;
			
			case SDL_TEXTINPUT:
			{
				mu_input_text(app->mui, event.text.text);
				
				KeyboardState_Type(&app->inputManager.keyboardState, event.text.text[0]);
			} break;
			
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			{
				InputManager_GamepadEventButton(&app->inputManager, event.cbutton);
			} break;
			
			case SDL_CONTROLLERAXISMOTION:
			{
				InputManager_GamepadEventAxis(&app->inputManager, event.caxis);
			} break;
			
			case SDL_CONTROLLERDEVICEADDED:
			{
				for(int i = 0; i < sizeof(app->inputManager.gamepadStates) / sizeof(GamepadState); i++)
				{
					if(app->inputManager.gamepadStates[i].instance == -1)
					{
						app->inputManager.gamepadStates[i] = GamepadState_Create(event.cdevice.which);
						
						break;
					}
				}
			} break;
			
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				for(int i = 0; i < sizeof(app->inputManager.gamepadStates) / sizeof(GamepadState); i++)
				{
					if(app->inputManager.gamepadStates[i].instance != event.cdevice.which)
					{
						continue;
					}
					
					GamepadState_Close(&app->inputManager.gamepadStates[i]);
				}
			} break;
			
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				int b = button_map[event.button.button & 0xff];
				if (b && event.type == SDL_MOUSEBUTTONDOWN)
				{
					mu_input_mousedown(app->mui, event.button.x, event.button.y, b);
				}
				else if (b && event.type == SDL_MOUSEBUTTONUP)
				{
					mu_input_mouseup(app->mui, event.button.x, event.button.y, b);
				}
			} break;
			
			case SDL_MOUSEMOTION:
			{
				mu_input_mousemove(app->mui, event.motion.x, event.motion.y);
			} break;
			
			case SDL_MOUSEWHEEL:
			{
				mu_input_scroll(app->mui, 0, event.wheel.y * -30);
			} break;
		}
	}
}
