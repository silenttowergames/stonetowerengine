#pragma once

#include "LuaScript.h"

LuaScript LuaScript_Load(const char* key);
void LuaScript_Execute(ApplicationState* app, LuaScript* script);
