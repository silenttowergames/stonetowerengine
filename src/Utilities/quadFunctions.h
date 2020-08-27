#pragma once

#include <flecs.h>
#include "quad.h"
#include "../Assets/Texture.h"

quad quad_Easy(float x, float y, float width, float height, float offsetX, float offsetY, float rotation);
quad quad_Frame(Texture* texture, int x, int y);
bool quad_Intersects(float ALeft, float ARight, float ATop, float ABottom, float BLeft, float BRight, float BTop, float BBottom);
