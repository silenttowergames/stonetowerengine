#include <math.h>
#include "RenderableFunctions.h"
#include "../../Assets/TiledJSONFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/quadFunctions.h"

void Renderable_Sprite_Render(SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
{
	Renderable* renderable = (Renderable*)_renderable;
	quad pos = quad_Easy(
		position.X,
		position.Y,
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
	
	SpriteBatch_AddQuad(spriteBatch, camera, renderable->texture->asset, pos, src);
}

void Renderable_Tilemap_Render(SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
{
	Renderable* renderable = (Renderable*)_renderable;
	
	if(renderable == NULL)
	{
		return;
	}
	
	TiledJSONLayer* tilemap = (TiledJSONLayer*)renderable->data;
	
	if(
		tilemap == NULL
		||
		strcmp(tilemap->type, "tilelayer") != 0
	)
	{
		return;
	}
	
	quad pos;
	quad src;
	int index;
	int tile;
	int2d frame;
	
	for(int Y = 0; Y < tilemap->size.Y; Y++)
	{
		for(int X = 0; X < tilemap->size.X; X++)
		{
			index = (Y * tilemap->size.X) + X;
			
			if(tilemap->tiles[index] == 0)
			{
				continue;
			}
			
			tile = tilemap->tiles[index] - 1;
			
			frame.X = tile % (renderable->texture->size.X / renderable->texture->tilesize.X);
			frame.Y = floor(tile / (renderable->texture->size.X / renderable->texture->tilesize.X));
			
			pos = quad_Easy(
				position.X + (X * renderable->texture->tilesize.X * renderable->scale.X),
				position.Y + (Y * renderable->texture->tilesize.Y * renderable->scale.Y),
				renderable->texture->tilesize.X * renderable->scale.X,
				renderable->texture->tilesize.Y * renderable->scale.Y,
				renderable->offset.X,
				renderable->offset.Y,
				0
			);
			src = quad_Frame(renderable->texture, frame.X, frame.Y);
			
			SpriteBatch_AddQuad(spriteBatch, camera, renderable->texture->asset, pos, src);
		}
	}
}
