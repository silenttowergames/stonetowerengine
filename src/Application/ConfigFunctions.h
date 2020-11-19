#pragma once

#include "Config.h"
#include "ApplicationState.h"

Config Config_Load(ApplicationState* app);
void Config_Save(ApplicationState* app, Config config);
void Config_Resize(ApplicationState* app, int sizeX, int sizeY, bool fullscreen);
