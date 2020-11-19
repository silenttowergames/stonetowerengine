#pragma once

#include "LuaScript.h"
#include "../Application/ApplicationState.h"

LuaScript LuaScript_Load(const char* key);
bool LuaScript_Execute(ApplicationState* app, LuaScript* script);
void LuaScript_Free(LuaScript* script);
