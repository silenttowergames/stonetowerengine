#pragma once

#include <flecs.h>

typedef enum GameDataAttributeType
{
    GAMEDATA_ERROR = -1,
    GAMEDATA_Int,
    GAMEDATA_Bool,
    GAMEDATA_Float,
    GAMEDATA_String,
} GameDataAttributeType;

typedef struct GameDataAttribute
{
    GameDataAttributeType type;
    const char* key;
    const char* header;
    int valueInt;
    bool valueBool;
    float valueFloat;
    const char* valueString;
} GameDataAttribute;

#define gdAttr(_header, _key, _value, T) (GameDataAttribute){ .type = GAMEDATA_ ## T, .key = _key, .header = _header, .value ## T = _value }
#define gdValue(_header, _key, T) (*mapGet(app->gameData.map, _header":"_key, GameDataAttribute*))->value ## T
