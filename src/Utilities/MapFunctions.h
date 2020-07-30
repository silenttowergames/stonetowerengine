#pragma once

#include <stdarg.h>
#include"Map.h"

Map Map_Create(int size, int count, ...);
int Map_Get(Map* map, const char* key);
