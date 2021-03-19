#include <SDL2/SDL.h>

#include "RenderingFunctions.h"
#include "../Logging/LoggerFunctions.h"

bool Rendering_Init(ApplicationState* app)
{
	if(app->graphicsDriver != NULL)
	{
		SDL_SetHint("FNA3D_FORCE_DRIVER", app->graphicsDriver);
	}
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0)
	{
		Logger_Log(&app->logger, "ERROR", SDL_GetError());
		
		return false;
	}
	
	return true;
}
