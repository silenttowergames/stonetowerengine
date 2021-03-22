#pragma once

#include "ASEpriteJSON.h"

ASEpriteJSON ASEpriteJSON_Load(ApplicationState* app, const char* key);
void ASEpriteJSON_Free(ASEpriteJSON* aseprite);
