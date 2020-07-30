#include <SDL2/SDL.h>
#include <flecs.h>
#include "SDLEventsSystem.h"
#include "../../Application/ApplicationState.h"

void SDLEventsSystem(ecs_iter_t* it)
{
	ApplicationState* app = (ApplicationState*)ecs_get_context(it->world);
	
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
						//AudioManager_focus(&app->audioManager);
						
						app->focused = true;
						
						break;
					}
					
					case SDL_WINDOWEVENT_FOCUS_LOST:
					{
						//AudioManager_blur(&app->audioManager);
						
						app->focused = false;
						
						break;
					}
				}
			} break;
			
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				//KeyboardState_Event(&app->keyboardState, event.key);
			} break;
			
			case SDL_TEXTINPUT:
			{
				//KeyboardState_Type(&app->keyboardState, event.text.text[0]);
			} break;
			
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			{
				//GamepadManager_EventButton(&app->gamepadManager, event.cbutton);
			} break;
			
			case SDL_CONTROLLERAXISMOTION:
			{
				//GamepadManager_EventAxis(&app->gamepadManager, event.caxis);
			}
		}
	}
}
