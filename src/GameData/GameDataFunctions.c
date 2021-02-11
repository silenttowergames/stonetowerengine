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
    
    printf("%s\n%s~%s\n", gameDataMapKey, header, key);
    
    GameDataAttribute** attr = mapGet(gameData->map, gameDataMapKey, GameDataAttribute*);
    
    return *attr;
}

void GameData_Free(GameData* gameData)
{
    ecs_map_free(gameData->map); // GameData.map free
    free(gameData->data); // GameData.data free
    free(gameData->filepath); // GameData.filepath free
    free(gameDataMapKey); // gameDataMapKey free
}
