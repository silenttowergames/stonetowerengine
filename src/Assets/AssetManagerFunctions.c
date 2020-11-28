#include "AssetManagerFunctions.h"
#include "../Audio/SoundFunctions.h"

AssetManager AssetManager_Create()
{
	AssetManager assetManager;
	memset(&assetManager, 0, sizeof(AssetManager));
	
	assetManager.lua = luaL_newstate();
	luaL_openlibs(assetManager.lua);
	
	return assetManager;
}

void AssetManager_Destroy(FNA3D_Device* device, AssetManager* assetManager)
{
	int i;
	
	ecs_map_free(assetManager->mapLua); // AssetManager.mapLua free
	ecs_map_free(assetManager->mapShader); // AssetManager.mapShader free
	ecs_map_free(assetManager->mapSound); // AssetManager.mapSound free
	ecs_map_free(assetManager->mapTexture); // AssetManager.mapTexture free
	ecs_map_free(assetManager->mapTiled); // AssetManager.mapTiled free
	ecs_map_free(assetManager->mapFont); // AssetManager.mapFont free
	
	for(i = 0; i < assetManager->lengthLua; i++)
	{
		LuaScript_Free(&assetManager->arrayLua[i]);
	}
	
	for(i = 0; i < assetManager->lengthShader; i++)
	{
		Shader_Free(device, &assetManager->arrayShader[i]);
	}
	
	for(i = 0; i < assetManager->lengthSound; i++)
	{
		Sound_Free(&assetManager->arraySound[i]);
	}
	
	for(i = 0; i < assetManager->lengthTexture; i++)
	{
		Texture_Free(device, &assetManager->arrayTexture[i]);
	}
	
	for(i = 0; i < assetManager->lengthTiled; i++)
	{
		TiledJSON_Free(&assetManager->arrayTiled[i]);
	}
	
	for(i = 0; i < assetManager->lengthFont; i++)
	{
		//Font_Free()
	}
	
	free(assetManager->arrayLua); // AssetManager.arrayLua free
	free(assetManager->arrayShader); // AssetManager.arrayShader free
	free(assetManager->arraySound); // AssetManager.arraySound free
	free(assetManager->arrayTexture); // AssetManager.arrayTexture free
	free(assetManager->arrayTiled); // AssetManager.arrayTiled free
	free(assetManager->arrayFont); // AssetManager.arrayFont free
	
	lua_close(assetManager->lua); // AssetManager.lua free
}

void AssetManager_InitTexture(AssetManager* assetManager, int length)
{
	assetManager->arrayTexture = malloc(sizeof(Texture) * length);
	assetManager->mapTexture = ecs_map_new(Texture*, length);
	assetManager->lengthTexture = length;
	assetManager->lengthSoFarTexture = 0;
}

void AssetManager_AddTexture(AssetManager* assetManager, Texture texture)
{
	assetManager->arrayTexture[assetManager->lengthSoFarTexture] = texture;
	
	Texture* pTex = &assetManager->arrayTexture[assetManager->lengthSoFarTexture];
	
	mapSet(assetManager->mapTexture, texture.key, &pTex);
	
	assetManager->lengthSoFarTexture++;
}

void AssetManager_AddTextures(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddTexture(assetManager, va_arg(args, Texture));
	}
	
	va_end(args);
}

void AssetManager_InitMap(AssetManager* assetManager, int length)
{
	assetManager->arrayTiled = malloc(sizeof(TiledJSON) * length);
	assetManager->mapTiled = ecs_map_new(TiledJSON*, length);
	assetManager->lengthTiled = length;
	assetManager->lengthSoFarTiled = 0;
}

void AssetManager_AddMap(AssetManager* assetManager, TiledJSON map)
{
	assetManager->arrayTiled[assetManager->lengthSoFarTiled] = map;
	
	TiledJSON* pMap = &assetManager->arrayTiled[assetManager->lengthSoFarTiled];
	mapSet(assetManager->mapTiled, map.key, &pMap);
	
	assetManager->lengthSoFarTiled++;
}

void AssetManager_AddMaps(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddMap(assetManager, va_arg(args, TiledJSON));
	}
	
	va_end(args);
}

void AssetManager_InitShader(AssetManager* assetManager, int length)
{
	assetManager->arrayShader = malloc(sizeof(Shader) * length);
	assetManager->mapShader = ecs_map_new(Shader*, length);
	assetManager->lengthShader = length;
	assetManager->lengthSoFarShader = 0;
}

void AssetManager_AddShader(AssetManager* assetManager, Shader shader)
{
	assetManager->arrayShader[assetManager->lengthSoFarShader] = shader;
	
	Shader* pShader = &assetManager->arrayShader[assetManager->lengthSoFarShader];
	mapSet(assetManager->mapShader, shader.key, &pShader);
	
	assetManager->lengthSoFarShader++;
}

void AssetManager_AddShaders(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddShader(assetManager, va_arg(args, Shader));
	}
	
	va_end(args);
}

void AssetManager_InitLua(AssetManager* assetManager, int length)
{
	assetManager->arrayLua = malloc(sizeof(LuaScript) * length);
	assetManager->mapLua = ecs_map_new(LuaScript*, length);
	assetManager->lengthLua = length;
	assetManager->lengthSoFarLua = 0;
}

void AssetManager_AddLua(AssetManager* assetManager, LuaScript script)
{
	assetManager->arrayLua[assetManager->lengthSoFarLua] = script;
	
	LuaScript* pScript = &assetManager->arrayLua[assetManager->lengthSoFarLua];
	mapSet(assetManager->mapLua, script.key, &pScript);
	
	assetManager->lengthSoFarLua++;
}

void AssetManager_AddLuas(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddLua(assetManager, va_arg(args, LuaScript));
	}
	
	va_end(args);
}

void AssetManager_InitSound(AssetManager* assetManager, int length)
{
	AudioManager_create(&assetManager->audioManager);
	
	assetManager->arraySound = malloc(sizeof(Sound) * length); // AssetManager.arraySound allocate
	assetManager->mapSound = ecs_map_new(Sound*, length); // AssetManager.mapSound allocate
	assetManager->lengthSound = length;
	assetManager->lengthSoFarSound = 0;
}

void AssetManager_AddSound(AssetManager* assetManager, Sound sound)
{
	assetManager->arraySound[assetManager->lengthSoFarSound] = sound;
	
	Sound* pSound = &assetManager->arraySound[assetManager->lengthSoFarSound];
	mapSet(assetManager->mapSound, sound.key, &pSound);
	
	assetManager->lengthSoFarSound++;
}

void AssetManager_AddSounds(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddSound(assetManager, va_arg(args, Sound));
	}
	
	va_end(args);
	
	AudioManager_addSounds(&assetManager->audioManager, assetManager->arraySound, assetManager->lengthSound);
}

void AssetManager_InitFont(AssetManager* assetManager, int length)
{
	AudioManager_create(&assetManager->audioManager);
	
	assetManager->arrayFont = malloc(sizeof(Font) * length); // AssetManager.arrayFont allocate
	assetManager->mapFont = ecs_map_new(Font*, length); // AssetManager.mapFont allocate
	assetManager->lengthFont = length;
	assetManager->lengthSoFarFont = 0;
}

void AssetManager_AddFont(AssetManager* assetManager, Font font)
{
	assetManager->arrayFont[assetManager->lengthSoFarFont] = font;
	
	Font* pFont = &assetManager->arrayFont[assetManager->lengthSoFarFont];
	mapSet(assetManager->mapFont, font.key, &pFont);
	
	assetManager->lengthSoFarFont++;
}

void AssetManager_AddFonts(AssetManager* assetManager, int length, ...)
{
	va_list args;
	
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		AssetManager_AddFont(assetManager, va_arg(args, Font));
	}
	
	va_end(args);
}
