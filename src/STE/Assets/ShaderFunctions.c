#include "../includes.h"
#include "ShaderFunctions.h"

Shader Shader_Create(ApplicationState* app, char* key, void (*update)(void*, void*, void*))
{
	Shader shader;
	memset(&shader, 0, sizeof(Shader));
	
	shader.update = update;
	
	const char* formatStr = "assets/shaders/%s.fxb";
	
	shader.key = key;
	
	shader.filename = malloc(sizeof(char) * (strlen(formatStr) + strlen(key) + 1 - 2)); // Shader.filename allocate
	sprintf(shader.filename, formatStr, shader.key);
	
	FILE *effectFile = fopen(shader.filename, "rb");
	
	if(effectFile == NULL)
	{
		Logger_Log(&app->logger, "Shader Not Found", shader.filename);
		
		assert(effectFile != NULL);
	}
	
	fseek(effectFile, 0, SEEK_END);
	uint32_t effectCodeLength = ftell(effectFile);
	fseek(effectFile, 0, SEEK_SET);
	uint8_t *effectCode = malloc(effectCodeLength);
	fread(effectCode, 1, effectCodeLength, effectFile);
	fclose(effectFile);
	
	FNA3D_CreateEffect(app->renderState.device, effectCode, effectCodeLength, &shader.effect, &shader.effectData);
	
	free(effectCode);
	
	return shader;
}

MOJOSHADER_effectParam* Shader_ParamGet(Shader* shader, const char* key)
{
	for(int i = 0; i < shader->effectData->param_count; i++)
	{
		if(strcmp(key, shader->effectData->params[i].value.name) == 0)
		{
			return &shader->effectData->params[i];
		}
	}
	
	return NULL;
}

bool Shader_ParamCopy(Shader* shader, const char* key, void* payload, size_t size)
{
	MOJOSHADER_effectParam* param = Shader_ParamGet(shader, key);
	
	if(param == NULL)
	{
		return false;
	}
	
	memcpy(param->value.values, payload, size);
	
	return true;
}

void Shader_Free(FNA3D_Device* device, Shader* shader)
{
	free(shader->filename);
	
	FNA3D_AddDisposeEffect(device, shader->effect);
}
