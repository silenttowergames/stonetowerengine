#include "RenderableFunctions.h"
#include "Body.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/quadFunctions.h"

void Renderable_Sprite_Render(SpriteBatch* spriteBatch, void* _renderable, Body* body)
{
	Renderable* renderable = (Renderable*)_renderable;
	quad pos = quad_Easy(
		body->position.X,
		body->position.Y,
		renderable->texture->tilesize.X * renderable->scale.X,
		renderable->texture->tilesize.Y * renderable->scale.Y,
		renderable->offset.X * renderable->scale.X,
		renderable->offset.Y * renderable->scale.Y
	);
	quad src = quad_Frame(renderable->texture, renderable->frame.X, renderable->frame.Y);
	
	SpriteBatch_AddQuad(spriteBatch, pos, src);
}

Renderable Renderable_Sprite_New(Texture* texture)
{
	Renderable renderable;
	memset(&renderable, 0, sizeof(Renderable));
	
	renderable.texture = texture;
	renderable.scale.X = 1;
	renderable.scale.Y = 1;
	renderable.render = Renderable_Sprite_Render;
	
	return renderable;
}
