#pragma once

#include "Shader.h"

Shader Shader_Create(FNA3D_Device* device, char* key, void (*update)(void*, void*));
MOJOSHADER_effectParam* Shader_ParamGet(Shader* shader, const char* key);
bool Shader_ParamCopy(Shader* shader, const char* key, void* payload, size_t size);
void Shader_Free(Shader* shader);
