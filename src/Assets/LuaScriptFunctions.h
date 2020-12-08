#pragma once

#include "LuaScript.h"
#include "../Application/ApplicationState.h"

LuaScript LuaScript_Load(const char* key);
void LuaScript_Free(LuaScript* script);
