#pragma once

#include <flecs.h>

typedef struct TiledJSONProperty
{
    const char* key;
    const char* type;
    const char* valueString;
    bool valueBool;
    int valueInt;
    int valueFloat;
} TiledJSONProperty;
