#pragma once

#include "GameData.h"
#include "GameDataAttribute.h"

GameData GameData_Create(ApplicationState* app, const char* filename, int length);
void GameData_AddAll(GameData* gameData, int length, ...);
GameDataAttribute* GameData_Get(GameData* gameData, const char* header, const char* key);
void GameData_Free(GameData* gameData);
