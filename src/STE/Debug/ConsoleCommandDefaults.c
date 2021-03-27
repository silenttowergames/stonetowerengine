#include "ConsoleCommandDefaults.h"
#include "../Assets/TiledJSONFunctions.h"
#include "../ECS/Components/TiledObject.h"

void cmdPlaySound(ApplicationState* app, int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        soundPlay(argv[i]);
    }
}

void cmdVolume(ApplicationState* app, int argc, char** argv)
{
    if(argc != 2 || argv[0] == NULL || argv[1] == NULL)
    {
        return;
    }
    
    uint64_t keyMaster = Flecs_Map_Key("master");
    uint64_t keyMusic = Flecs_Map_Key("music");
    uint64_t keySFX = Flecs_Map_Key("sfx");
    uint64_t key = Flecs_Map_Key(argv[0]);
    float* value;
    float volume;
    
    if(key == keyMusic)
    {
        value = &app->config.volumeMusic;
    }
    else if(key == keyMaster)
    {
        value = &app->config.volumeMaster;
    }
    else if(key == keySFX)
    {
        value = &app->config.volumeSFX;
    }
    else
    {
        return;
    }
    
    volume = strtof(argv[1], NULL);
    
    *value = volume;
    
    printf("M: %f\nS: %f\nM: %f\n", app->config.volumeMaster, app->config.volumeSFX, app->config.volumeMusic);
}

void cmdChangeScene(ApplicationState* app, int argc, char** argv)
{
    for(int i = 0; i < argc; i++)
    {
        ApplicationState_SetScene(app, argv[i]);
        
        break;
    }
}

void cmdExit(ApplicationState* app, int argc, char** argv)
{
    app->quit = true;
}

void cmdMovable(ApplicationState* app, int argc, char** argv)
{
    app->movable = !app->movable;
}

void cmdPause(ApplicationState* app, int argc, char** argv)
{
    ecs_set_time_scale(app->world, 0.0f);
}

void cmdUnpause(ApplicationState* app, int argc, char** argv)
{
    ecs_set_time_scale(app->world, 1.0f);
}

void cmdReloadMap(ApplicationState* app, int argc, char** argv)
{
    // First, find the map we want to reload
    const char* key;
    
    // If the user doesn't specify a map, assume the one that's currently loaded
    if(argc == 0 || argv[0][0] == '\0')
    {
        key = app->flecsSceneCurrent;
    }
    else
    {
        key = argv[0];
    }
    
    TiledJSON** _map = mapGet(app->assetManager.mapTiled, key, TiledJSON*);
    
    // If the map doesn't exist, just return
    // Maybe in the future there will be feedback from the console
    if(_map == NULL)
    {
        return;
    }
    
    TiledJSON* map = *_map;
    TiledJSON oldMap = *map;
    
    TiledJSON newMap = TiledJSON_Load(app, oldMap.key);
    
    if(strcmp(key, app->flecsSceneCurrent) == 0)
    {
        TiledJSONObject* objIDsOld = malloc(sizeof(TiledJSONObject) * map->objCount);
        TiledJSONObject* objIDsNew = malloc(sizeof(TiledJSONObject) * newMap.objCount);
        
        int currentCountOld = 0;
        int currentCountNew = 0;
        for(int i = 0; i < fmax(map->objCount, newMap.objCount); i++)
        {
            if(i < map->objCount)
            {
                for(int j = 0; j < map->layerCount; j++)
                {
                    if(strcmp(map->layers[j].type, "tilelayer") == 0)
                    {
                        continue;
                    }
                    
                    if((i - currentCountOld) >= map->layers[j].count)
                    {
                        currentCountOld += map->layers[j].count;
                        
                        continue;
                    }
                    
                    objIDsOld[i] = map->layers[j].objects[i - currentCountOld];
                }
            }
            
            if(i < newMap.objCount)
            {
                for(int j = 0; j < newMap.layerCount; j++)
                {
                    if(strcmp(newMap.layers[j].type, "tilelayer") == 0)
                    {
                        continue;
                    }
                    
                    if((i - currentCountNew) >= newMap.layers[j].count)
                    {
                        currentCountNew += newMap.layers[j].count;
                        
                        continue;
                    }
                    
                    objIDsNew[i] = newMap.layers[j].objects[i - currentCountNew];
                }
            }
        }
        
        ecs_query_t* query;
        ecs_iter_t it;
        
        query = ecs_query_new(app->world, "TiledMap");
        
        it = ecs_query_iter(query);
        
        while(ecs_query_next(&it))
        {
            for(int i = 0; i < it.count; i++)
            {
                ecs_delete(app->world, it.entities[i]);
            }
        }
        
        ecs_query_free(query);
        
        for(int i = 0; i < newMap.layerCount; i++)
        {
            if(strcmp(newMap.layers[i].type, "tilelayer") != 0)
            {
                continue;
            }
            
            TiledJSON_Map(app->world, &newMap.layers[i], newMap.texture, i);
        }
        
        query = ecs_query_new(app->world, "TiledObject");
        it = ecs_query_iter(query);
        
        while(ecs_query_next(&it))
        {
            TiledObject* obj = ecs_column(&it, TiledObject, 1);
            
            for(int i = 0; i < it.count; i++)
            {
                bool delete = true;
                
                for(int j = 0; j < newMap.objCount; j++)
                {
                    if(objIDsNew[j].id == obj[i].id)
                    {
                        delete = false;
                        
                        break;
                    }
                }
                
                if(delete)
                {
                    ecs_delete(app->world, it.entities[i]);
                }
            }
        }
        
        ecs_query_free(query);
        
        for(int i = 0; i < newMap.objCount; i++)
        {
            bool isNew = true;
            
            for(int j = 0; j < map->objCount; j++)
            {
                if(objIDsNew[i].id == objIDsOld[j].id)
                {
                    isNew = false;
                    
                    break;
                }
            }
            
            if(isNew)
            {
                TiledJSON_Build_Object(app, &objIDsNew[i], objIDsNew[i].layer);
            }
        }
        
        free(objIDsOld);
        free(objIDsNew);
    }
    
    for(int i = 0; i < app->assetManager.lengthTiled; i++)
    {
        if(strcmp(app->assetManager.arrayTiled[i].key, key) != 0)
        {
            continue;
        }
        
        app->assetManager.arrayTiled[i] = newMap;
        
        break;
    }
    
    TiledJSON_Free(&oldMap);
}

void cmdWebsite(ApplicationState* app, int argc, char** argv)
{
    if(argc <= 0)
    {
        return;
    }
    
    SDL_OpenURL(argv[0]);
}
