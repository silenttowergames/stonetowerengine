#include <flecs.h>
#include "../ECS/FlecsFunctions.h"
#include "GameDataFunctions.h"

static char* gameDataMapKey = NULL;

GameData GameData_Create(ApplicationState* app, const char* filename, int length)
{
    if(gameDataMapKey == NULL)
    {
        gameDataMapKey = malloc(sizeof(char) * 1024); // gameDataMapKey allocate
    }
    
    GameData gameData;
    memset(&gameData, 0, sizeof(GameData));
    
    gameData.filename = filename;
    
    gameData.filepath = malloc(sizeof(char) * (strlen(app->savePath) + strlen(gameData.filename) + 1)); // GameData.filepath allocate
    sprintf(gameData.filepath, "%s%s", app->savePath, gameData.filename);
    
    return gameData;
}

void GameData_AddAll(GameData* gameData, int length, ...)
{
    gameData->length = length;
    gameData->data = malloc(sizeof(GameDataAttribute) * gameData->length); // GameData.data allocate
    gameData->map = ecs_map_new(GameDataAttribute*, gameData->length); // GameData.map allocate
    
    va_list args;
    GameDataAttribute attr;
    GameDataAttribute* pattr;
    
    va_start(args, length);
    
    for(int i = 0; i < length; i++)
    {
        attr = va_arg(args, GameDataAttribute);
        
        gameData->data[i] = attr;
        
        pattr = &gameData->data[i];
        
        sprintf(gameDataMapKey, "%s~%s\n", attr.header, attr.key);
        
        mapSet(gameData->map, gameDataMapKey, &pattr);
    }
    
    va_end(args);
}

GameDataAttribute* GameData_Get(GameData* gameData, const char* header, const char* key)
{
    sprintf(gameDataMapKey, "%s~%s\n", header, key);
    
    GameDataAttribute** attr = mapGet(gameData->map, gameDataMapKey, GameDataAttribute*);
    
    return *attr;
}

void GameData_Load(GameData* gameData)
{
    ini_t* r = ini_load(gameData->filepath);
    char* str;
    
    if(r == NULL)
    {
        return;
    }
    
    for(int i = 0; i < gameData->length; i++)
    {
        GameDataAttribute* attr = &gameData->data[i];
        
        switch(attr->type)
        {
            case GAMEDATA_Int:
            {
                ini_sget(r, attr->header, attr->key, "%d", &attr->valueInt);
            } break;
            
            case GAMEDATA_Bool:
            {
                ini_sget(r, attr->header, attr->key, "%d", &attr->valueBool);
            } break;
            
            case GAMEDATA_Float:
            {
                ini_sget(r, attr->header, attr->key, "%.*f", &attr->valueFloat);
            } break;
            
            case GAMEDATA_String:
            {
                str = (char*)ini_get(r, attr->header, attr->key);
                
                if(str == NULL)
                {
                    break;
                }
                
                if(attr->wasAllocated)
                {
                    free(attr->valueString);
                }
                
                attr->valueString = malloc(sizeof(char) * (strlen(str) + 1));
                strcpy(attr->valueString, str);
                
                attr->wasAllocated = true;
            } break;
        }
    }
}

void GameData_Save(GameData* gameData)
{
    FILE* gdINI = fopen(gameData->filepath, "w");
    char* header = NULL;
    for(int i = 0; i < gameData->length; i++)
    {
        GameDataAttribute* attr = &gameData->data[i];
        
        if(header != attr->header)
        {
            if(header != NULL)
            {
                fprintf(gdINI, "\n", attr->header);
            }
            
            fprintf(gdINI, "[%s]\n", attr->header);
            
            header = (char*)attr->header;
        }
        
        switch(attr->type)
        {
            case GAMEDATA_Int:
            {
                fprintf(gdINI, "%s = %d\n", attr->key, attr->valueInt);
            } break;
            
            case GAMEDATA_Bool:
            {
                fprintf(gdINI, "%s = %d\n", attr->key, attr->valueBool);
            } break;
            
            case GAMEDATA_Float:
            {
                fprintf(gdINI, "%s = %.*f\n", attr->key, attr->valueFloat);
            } break;
            
            case GAMEDATA_String:
            {
                fprintf(gdINI, "%s = \"%s\"\n", attr->key, attr->valueString);
            } break;
        }
    }
    fclose(gdINI);
}

void GameData_Free(GameData* gameData)
{
    for(int i = 0; i < gameData->length; i++)
    {
        if(gameData->data[i].type == GAMEDATA_String && gameData->data[i].wasAllocated)
        {
            free(gameData->data[i].valueString);
        }
    }
    
    ecs_map_free(gameData->map); // GameData.map free
    free(gameData->data); // GameData.data free
    free(gameData->filepath); // GameData.filepath free
    free(gameDataMapKey); // gameDataMapKey free
}
