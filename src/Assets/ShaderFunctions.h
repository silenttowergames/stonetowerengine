#pragma once

#include "Shader.h"

Shader Shader_Create(FNA3D_Device* device, char* key);
void Shader_Free(Shader* shader);
