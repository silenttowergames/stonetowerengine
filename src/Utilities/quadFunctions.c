#include "quadFunctions.h"

quad quad_Easy(float x, float y, float width, float height, float offsetX, float offsetY)
{
	float wd2 = width / 2;
	float hd2 = height / 2;
	
	return (quad){
		{ x - offsetX, y - offsetY, },
		{ x + width - offsetX, y - offsetY, },
		{ x - offsetX, y + height - offsetY, },
		{ x + width - offsetX, y + height - offsetY, },
	};
}

quad quad_Frame(Texture* texture, int x, int y)
{
	float2d pos = {
		(x * (texture->tilesize.X + texture->padding.X)) + texture->border.X,
		(y * (texture->tilesize.Y + texture->padding.Y)) + texture->border.Y,
	};
	
	quad q = quad_Easy(
		pos.X, 
		pos.Y,
		texture->tilesize.X,
		texture->tilesize.Y,
		0,
		0
	);
	
	q.topLeft.X = 1.0f / (texture->size.X / q.topLeft.X);
	q.topLeft.Y = 1.0f / (texture->size.Y / q.topLeft.Y);
	q.topRight.X = 1.0f / (texture->size.X / q.topRight.X);
	q.topRight.Y = 1.0f / (texture->size.Y / q.topRight.Y);
	
	q.bottomLeft.X = 1.0f / (texture->size.X / q.bottomLeft.X);
	q.bottomLeft.Y = 1.0f / (texture->size.Y / q.bottomLeft.Y);
	q.bottomRight.X = 1.0f / (texture->size.X / q.bottomRight.X);
	q.bottomRight.Y = 1.0f / (texture->size.Y / q.bottomRight.Y);
	
	return q;
}
