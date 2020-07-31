#pragma once

#include "Shader.h"

Shader Shader_Create(ApplicationState* app, char* key);
void Shader_Free(Shader* shader);
