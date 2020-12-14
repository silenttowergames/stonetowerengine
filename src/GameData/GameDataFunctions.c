#include "GameDataFunctions.h"

GameData GameData_Create(const char* filename)
{
    GameData gameData;
    memset(&gameData, 0, sizeof(GameData));
    
    return gameData;
}
