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
    
    ini_sget(r, "Config", "Width", "%d", &config.windowedSize.X);
    ini_sget(r, "Config", "Height", "%d", &config.windowedSize.Y);
    ini_sget(r, "Config", "Debug", "%d", &config.debug);
    ini_sget(r, "Config", "VolumeMaster", "%f", &config.volumeMaster);
    ini_sget(r, "Config", "VolumeSFX", "%f", &config.volumeSFX);
    ini_sget(r, "Config", "VolumeMusic", "%f", &config.volumeMusic);
    
    const char* language = ini_get(r, "Config", "Language");
    if(language)
    {
        if(config.language != NULL)
        {
            free(config.language);
        }
        
        config.language = malloc(sizeof(char) * (1 + strlen(language))); // config.language allocate
        
        strcpy(config.language, language);
    }
    
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
    
    fprintf(
        w,
        "[Config]\n"
        "Width = %d\n"
        "Height = %d\n"
        "Language = \"%s\"\n"
        "Vsync = %d\n"
        "Debug = %d\n"
        "VolumeMaster = %f\n"
        "VolumeSFX = %f\n"
        "VolumeMusic = %f\n",
        config.windowedSize.X,
        config.windowedSize.Y,
        config.language,
        config.vsync,
        config.debug,
        config.volumeMaster,
        config.volumeSFX,
        config.volumeMusic
    );
    
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

void Config_Free(Config* config)
{
    free(config->language);
}
