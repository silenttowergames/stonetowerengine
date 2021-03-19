#pragma once

#include <flecs.h>
#include "SpriteBatch.h"
#include "../Utilities/quad.h"

void SpriteBatch_Create(SpriteBatch* spriteBatch);
void SpriteBatch_Begin(SpriteBatch* spriteBatch);
void SpriteBatch_AddQuad(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, FNA3D_Texture* texture, quad pos, quad src, uint32_t color);
void SpriteBatch_Flush(RenderState* renderState);
void SpriteBatch_End(SpriteBatch* spriteBatch);
void SpriteBatch_Free(SpriteBatch* spriteBatch);
