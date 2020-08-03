#include "RenderableFunctions.h"

void Renderable_Sprite_Render(void* renderable)
{
	//
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
