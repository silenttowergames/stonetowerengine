#include "quadFunctions.h"

quad quad_Easy(float x, float y, float width, float height)
{
	return (quad){
		{ x, y, },
		{ x + width, y, },
		{ x, y + height, },
		{ x + width, y + height, },
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
		texture->tilesize.Y
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
