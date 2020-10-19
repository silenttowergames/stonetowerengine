#pragma once

#include "TiledJSON.h"
#include "../Application/ApplicationState.h"

TiledJSON TiledJSON_Load(ApplicationState* app, const char* key);
void TiledJSON_Build(ApplicationState* app, TiledJSON* tiled);
void TiledJSON_Map(ecs_world_t* world, TiledJSONLayer* layer, Texture* texture, int layerID);
void TiledJSON_Free(TiledJSON* tiled);
