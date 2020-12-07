#include <flecs.h>
#include "BasicAABB.h"
#include "HitboxFunctions.h"

ECS_DTOR(BasicAABB, ptr, {
    free(ptr->hitboxes); // Hitbox* free1
})

Hitbox Hitbox_CreateBasic(float2d size)
{
    Hitbox hitbox;
    memset(&hitbox, 0, sizeof(hitbox));
    
    hitbox.size = size;
    
    hitbox.solidBottom = true;
    hitbox.solidLeft = true;
    hitbox.solidRight = true;
    hitbox.solidTop = true;
    
    hitbox.active = true;
    
    return hitbox;
}

Hitbox Hitbox_CreateSquare(float size)
{
    return Hitbox_CreateBasic((float2d){ size, size, });
}

Hitbox* Hitbox_CreateList(int length, ...)
{
    Hitbox* hitboxes = malloc(sizeof(Hitbox) * length); // Hitbox* allocate
    
    va_list args;
    
	va_start(args, length);
	
	for(int i = 0; i < length; i++)
	{
		hitboxes[i] = va_arg(args, Hitbox);
	}
	
	va_end(args);
    
    return hitboxes;
}

walls Hitbox_GetWalls(Hitbox* hitbox, float2d position)
{
    walls h;
    memset(&h, 0, sizeof(h));
    
    float2d sUnit;
    sUnit.X = hitbox->size.X / 2;
    sUnit.Y = hitbox->size.Y / 2;
    
    h.top = position.Y + hitbox->offset.Y - (hitbox->size.X / 2);
    h.bottom = h.top + hitbox->size.X;
    
    h.left = position.X + hitbox->offset.X - (hitbox->size.Y / 2);
    h.right = h.left + hitbox->size.Y;
    
    return h;
}
