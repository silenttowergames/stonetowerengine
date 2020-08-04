#pragma once

#include "Renderable.h"

void Renderable_Sprite_Render(SpriteBatch* spriteBatch, void* renderable, Body* body);
Renderable Renderable_Sprite_New(Texture* texture);
