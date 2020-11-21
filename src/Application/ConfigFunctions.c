#include <stdio.h>
#include "ConfigFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

Config Config_Load(ApplicationState* app)
{
    Config config;
    
    FILE* r = fopen(app->savePathConfig, "rb");
    
    if(r == NULL)
    {
        return app->config;
    }
    
    fseek(r, 0, SEEK_END);
    uint32_t rLength = ftell(r);
    fseek(r, 0, SEEK_SET);
    
    if(rLength != sizeof(config))
    {
        return app->config;
    }
    
    fread(&config, sizeof(config), 1, r);
    fclose(r);
    
    return config;
}

void Config_Save(ApplicationState* app, Config config)
{
    config.fullscreen = false;
    
    FILE* w = fopen(app->savePathConfig, "wb");
    fwrite(&config, sizeof(config), 1, w);
    fclose(w);
}

void Config_Resize(ApplicationState* app, int sizeX, int sizeY, bool fullscreen)
{
    if(fullscreen)
    {
        SDL_Rect rect;
        int m = SDL_GetWindowDisplayIndex(app->renderState.window);
        
        SDL_GetDisplayBounds(m, &rect);
        
        sizeX = rect.w;
        sizeY = rect.h;
    }
    
    app->config.size.X = sizeX;
    app->config.size.Y = sizeY;
    
    printf("%dx%d\n", app->config.size.X, app->config.size.Y);
    
    if(!fullscreen)
    {
        app->config.windowedSize = app->config.size;
    }
    
    app->config.fullscreen = fullscreen;
    
    SDL_SetWindowFullscreen(app->renderState.window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    
    RenderState_Resize(app, sizeX, sizeY);
    
    SDL_SetWindowPosition(app->renderState.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
