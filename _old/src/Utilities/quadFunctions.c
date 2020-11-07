#include "quadFunctions.h"
#include <SDL2/SDL.h>

quad quad_Easy(float x, float y, float width, float height, float offsetX, float offsetY, float rotation)
{
	rotation *= -1;
	
	float wd2 = width / 2;
	float hd2 = height / 2;
	
	float rTopLeft = (rotation + 180 + 90 + 45) * (M_PI / 180);
	float rTopRight = (rotation + 45) * (M_PI / 180);
	float rBottomLeft = (rotation + 180 + 45) * (M_PI / 180);
	float rBottomRight = (rotation + 90 + 45) * (M_PI / 180);
	
	float hypo = sqrtf((wd2 * wd2) + (hd2 * hd2));
	
	return (quad){
		{ x + (hypo * sin(rTopLeft)) - offsetX, y + (hypo * cos(rTopLeft)) - offsetY, },
		{ x + (hypo * sin(rTopRight)) - offsetX, y + (hypo * cos(rTopRight)) - offsetY, },
		{ x + (hypo * sin(rBottomLeft)) - offsetX, y + (hypo * cos(rBottomLeft)) - offsetY, },
		{ x + (hypo * sin(rBottomRight)) - offsetX, y + (hypo * cos(rBottomRight)) - offsetY, },
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
		-(texture->tilesize.X / 2),
		-(texture->tilesize.Y / 2),
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

bool quad_Intersects(float ALeft, float ARight, float ATop, float ABottom, float BLeft, float BRight, float BTop, float BBottom)
{
	if(
		!(ARight >= BLeft && ALeft <= BLeft)
		&&
		!(ARight >= BRight && ALeft <= BRight)
	)
	{
		return false;
	}
	
	// If we've made it this far, we're intersecting on X
	
	if(
		!(ABottom >= BTop && ATop <= BTop)
		&&
		!(ABottom >= BBottom && ATop <= BBottom)
	)
	{
		return false;
	}
	
	// If we've made it this far, we're intersecting on X and Y
	
	return true;
}
