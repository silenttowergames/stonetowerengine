#pragma once

#include "quad.h"
#include "../Assets/Texture.h"

quad quad_Easy(float x, float y, float width, float height, float offsetX, float offsetY);
quad quad_Frame(Texture* texture, int x, int y);
