#include <stdio.h>
#include <lua.h>
#include <SDL2/SDL.h>
#include "LuaScriptFunctions.h"

LuaScript LuaScript_Load(const char* key)
{
	LuaScript script;
	
	script.key = key;
	
	const char* formatStr = "assets/scripts/%s.lua";
	script.filename = malloc(sizeof(char) * (strlen(formatStr) - 2 + 1 + strlen(key))); // LuaScript.filename allocate
	sprintf(script.filename, formatStr, script.key);
	
	FILE* f = fopen(script.filename, "rb");
	fseek(f, 0, SEEK_END);
	uint32_t length = ftell(f);
	fseek(f, 0, SEEK_SET);
	script.data = malloc(sizeof(char) * (length + 1)); // LuaScript.data allocate
	fread(script.data, 1, length, f);
	fclose(f);
	
	script.data[length] = '\0';
	
	return script;
}

void LuaScript_Execute(ApplicationState* app, LuaScript* script)
{
	int r = luaL_dostring(app->assetManager.lua, script->data);
    if(r == LUA_OK)
    {
        lua_getglobal(app->assetManager.lua, "a");
        
        if(lua_isnumber(app->assetManager.lua, -1))
        {
            float a = (float)lua_tonumber(app->assetManager.lua, -1);
            
            printf("%1.5f\n", a);
        }
    }
    else
    {
		Logger_Log(&app->logger, "ERROR_LUA", lua_tostring(app->assetManager.lua, -1));
    }
}

void LuaScript_Free(LuaScript* script)
{
	free(script->filename); // LuaScript.filename free
	free(script->data); // LuaScript.data free
}
