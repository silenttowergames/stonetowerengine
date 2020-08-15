#pragma once

#include "TiledJSON.h"
#include "../Application/ApplicationState.h"

TiledJSON TiledJSON_Load(ApplicationState* app, const char* key);
void TiledJSON_Build(ApplicationState* app, TiledJSON* tiled);
