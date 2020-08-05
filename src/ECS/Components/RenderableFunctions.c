#include <math.h>
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
		renderable->offset.Y * renderable->scale.Y,
		renderable->rotation
	);
	quad src = quad_Frame(renderable->texture, renderable->frame.X, renderable->frame.Y);
	
	if(renderable->flipX || renderable->flipY)
	{
		float swap;
		
		if(renderable->flipX)
		{
			swap = src.topLeft.X;
			
			src.topLeft.X = src.topRight.X;
			src.bottomLeft.X = src.bottomRight.X;
			
			src.topRight.X = swap;
			src.bottomRight.X = swap;
		}
		
		if(renderable->flipY)
		{
			swap = src.topLeft.Y;
			
			src.topLeft.Y = src.bottomLeft.Y;
			src.topRight.Y = src.bottomRight.Y;
			
			src.bottomLeft.Y = swap;
			src.bottomRight.Y = swap;
		}
	}
	
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
