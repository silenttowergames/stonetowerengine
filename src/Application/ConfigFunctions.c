#include "ConfigFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

void Config_Resize(ApplicationState* app, int sizeX, int sizeY, bool fullscreen)
{
    SDL_SetWindowFullscreen(app->renderState.window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    RenderState_Resize(app, sizeX, sizeY);
    
    app->config.size.X = sizeX;
    app->config.size.Y = sizeY;
    app->config.fullscreen = fullscreen;
}
