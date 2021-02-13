#pragma once

#include "GameData.h"
#include "GameDataAttribute.h"

GameData GameData_Create(ApplicationState* app, const char* filename, int length);
void GameData_AddAll(GameData* gameData, int length, ...);
GameDataAttribute* GameData_Get(GameData* gameData, const char* header, const char* key);
void GameData_Load(GameData* gameData);
void GameData_Save(GameData* gameData);
void GameData_Free(GameData* gameData);

#define gameDataInit(length, ...) app.gameData = GameData_Create(&app, "save.ini", length); GameData_AddAll(&app.gameData, length, __VA_ARGS__); GameData_Load(&app.gameData);
