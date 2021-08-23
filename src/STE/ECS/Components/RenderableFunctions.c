#include <math.h>
#include "RenderableFunctions.h"
#include "../../Application/ApplicationState.h"
#include "../../Assets/FontStashFNA3D.h"
#include "../../Assets/TiledJSONFunctions.h"
#include "../../Rendering/SpriteBatchFunctions.h"
#include "../../Utilities/quadFunctions.h"

quad Renderable_Sprite_GetPosQuad(Renderable* renderable, float2d position)
{
	return quad_Easy(
		position.X,
		position.Y,
		renderable->texture->tilesize.X * renderable->scale.X,
		renderable->texture->tilesize.Y * renderable->scale.Y,
		renderable->offset.X * renderable->scale.X,
		renderable->offset.Y * renderable->scale.Y,
		renderable->rotation
	);
}

void Renderable_Sprite_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
{
	Renderable* renderable = (Renderable*)_renderable;
	
	float2d _position = position;
	_position.X += (camera->position.X * (1 - renderable->parallax));
	_position.Y += (camera->position.Y * (1 - renderable->parallax));
	
	quad pos = Renderable_Sprite_GetPosQuad(renderable, _position);
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
	
	SpriteBatch_AddQuad(app, spriteBatch, camera, renderable->texture->asset, pos, src, renderable->color);
}

void Renderable_TextBox_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
{
	Renderable* renderable = (Renderable*)_renderable;
	
	float2d _position = position;
	_position.X += (camera->position.X * (1 - renderable->parallax));
	_position.Y += (camera->position.Y * (1 - renderable->parallax));
	
	const char* message = (const char*)renderable->data;
	
	if(message == NULL || strlen(message) == 0)
	{
		renderable->duration = 0;
	}
	
	renderable->duration++;
	
	FontStashFNA3D* fna = (FontStashFNA3D*)app->fons->params.userPtr;
	
	fna->renderable = renderable;
	
	fonsSetFont(app->fons, renderable->scale.X);
	fonsSetSize(app->fons, renderable->scale.Y);
	fonsSetColor(app->fons, renderable->color);
	fonsDrawText(app->fons, _position.X, _position.Y, message, NULL);
}

void Renderable_Tilemap_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
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
	
	int Left = ((camera->position.X - position.X - (camera->resolution.X / 2)) / renderable->texture->tilesize.X) + 1;
	int Top = ((camera->position.Y - position.Y - (camera->resolution.Y / 2)) / renderable->texture->tilesize.Y) + 1;
	int Right = ((camera->position.X - position.X + (camera->resolution.X / 2)) / renderable->texture->tilesize.X) + 2;
	int Bottom = ((camera->position.Y - position.Y + (camera->resolution.Y / 2)) / renderable->texture->tilesize.Y) + 2;
	
	for(int Y = fmax(0, Top); Y < Bottom; Y++)
	{
		if(Y >= tilemap->size.Y)
		{
			break;
		}
		
		for(int X = fmax(0, Left); X < Right; X++)
		{
			if(X >= tilemap->size.X)
			{
				break;
			}
			
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
			
			SpriteBatch_AddQuad(app, spriteBatch, camera, renderable->texture->asset, pos, src, renderable->color);
		}
	}
}

void Renderable_Box_Render(ApplicationState* app, SpriteBatch* spriteBatch, Camera* camera, void* _renderable, float2d position)
{
	Renderable* renderable = (Renderable*)_renderable;
	
	float2d _position = position;
	_position.X += (camera->position.X * (1 - renderable->parallax));
	_position.Y += (camera->position.Y * (1 - renderable->parallax));
	
	quad pos = {
        { _position.X - (renderable->scale.X / 2), _position.Y - (renderable->scale.Y / 2), },
        { _position.X + (renderable->scale.X / 2), _position.Y - (renderable->scale.Y / 2), },
        { _position.X - (renderable->scale.X / 2), _position.Y + (renderable->scale.Y / 2), },
        { _position.X + (renderable->scale.X / 2), _position.Y + (renderable->scale.Y / 2), },
    };
	quad src = {
        { 0, 0, },
        { 1, 0, },
        { 0, 1, },
        { 1, 1, },
    };
    
	SpriteBatch_AddQuad(app, spriteBatch, camera, app->renderState.blankTexture.asset, pos, src, renderable->color);
}
