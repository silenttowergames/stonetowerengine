#pragma once

#include "Font.h"
#include "../Application/ApplicationState.h"

Font Font_Create(ApplicationState* app, const char* key);
void Font_Free(Font* font);
