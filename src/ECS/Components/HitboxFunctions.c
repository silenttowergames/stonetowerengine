#include "HitboxFunctions.h"

Hitbox Hitbox_CreateBasic(float2d size)
{
    Hitbox hitbox;
    memset(&hitbox, 0, sizeof(hitbox));
    
    hitbox.size = size;
    
    hitbox.solidBottom = true;
    hitbox.solidLeft = true;
    hitbox.solidRight = true;
    hitbox.solidTop = true;
    
    return hitbox;
}

Hitbox Hitbox_CreateSquare(float size)
{
    return Hitbox_CreateBasic((float2d){ size, size, });
}

Hitbox* Hitbox_CreateList(int length, ...)
{
    Hitbox* hitboxes = malloc(sizeof(Hitbox) * length);
    
    va_list args;
    
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		hitboxes[i] = va_arg(args, Hitbox);
	}
	
	va_end(args);
    
    return hitboxes;
}
