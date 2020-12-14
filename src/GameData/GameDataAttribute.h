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
    int valueInt;
    bool valueBool;
    float valueFloat;
    const char* valueString;
} GameDataAttribute;

#define gdAttr(_key, _value, T) (GameDataAttribute){ .type = GAMEDATA_ ## T, .key = _key, .value ## T = _value }
