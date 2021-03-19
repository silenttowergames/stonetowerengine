#include <stdio.h>
#include "../includes_libs.h"
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

void LuaScript_Free(LuaScript* script)
{
	free(script->filename); // LuaScript.filename free
	free(script->data); // LuaScript.data free
}
