#pragma once

#include "LuaScript.h"
#include "../Application/ApplicationState.h"

LuaScript LuaScript_Load(ApplicationState* app, const char* key);
void LuaScript_Free(LuaScript* script);
