#pragma once

#include <flecs.h>
#include "SpriteBatch.h"
#include "../Utilities/quad.h"

void SpriteBatch_Create(SpriteBatch* spriteBatch);
bool SpriteBatch_Begin(SpriteBatch* spriteBatch);
void SpriteBatch_AddQuad(SpriteBatch* spriteBatch, Camera* camera, FNA3D_Texture* texture, quad pos, quad src);
void SpriteBatch_Flush(RenderState* renderState);
bool SpriteBatch_End(SpriteBatch* spriteBatch);
