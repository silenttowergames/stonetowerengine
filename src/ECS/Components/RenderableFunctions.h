#pragma once

#include "Renderable.h"
#include "../../Application/ApplicationState.h"

quad Renderable_Sprite_GetPosQuad(Renderable* renderable, float2d position);
void Renderable_Sprite_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position);
void Renderable_TextBox_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position);
void Renderable_Tilemap_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position);
