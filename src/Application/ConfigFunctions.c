#include <stdio.h>
#include "ConfigFunctions.h"
#include "../Rendering/RenderStateFunctions.h"

Config Config_Load(ApplicationState* app)
{
    Config config = app->config;
    
    ini_t* r = ini_load(app->savePathConfig);
    
    if(r == NULL)
    {
        return config;
    }
    
    // TODO: config.ini add language
    // The issue is, when doing `ini_free`, it will free the language string
    // This should be a painfully simple fix lol
    ini_sget(r, "Config", "Width", "%d", &config.windowedSize.X);
    ini_sget(r, "Config", "Height", "%d", &config.windowedSize.Y);
    
    int vsync;
    if(ini_sget(r, "Config", "Vsync", "%d", &vsync))
    {
        if(vsync)
        {
            config.vsync = true;
        }
        else
        {
            config.vsync = false;
        }
    }
    
    config.size = config.windowedSize;
    
    ini_free(r);
    
    return config;
}

void Config_Save(ApplicationState* app, Config config)
{
    FILE* w = fopen(app->savePathConfig, "w");
    fprintf(w, "[Config]\nWidth = %d\nHeight = %d\nVsync = %d\n", config.windowedSize.X, config.windowedSize.Y, config.vsync);
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
    
    if(!fullscreen)
    {
        app->config.windowedSize = app->config.size;
    }
    
    app->config.fullscreen = fullscreen;
    
    SDL_SetWindowFullscreen(app->renderState.window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    
    RenderState_Resize(app, sizeX, sizeY);
    
    SDL_SetWindowPosition(app->renderState.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
