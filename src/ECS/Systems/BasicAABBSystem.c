#include "BasicAABBSystem.h"

void BasicAABBSystem(ecs_iter_t* it)
{
    fctx();
	
    BasicAABB* a = ecs_column(it, BasicAABB, 1);
    Body* b = ecs_column(it, Body, 2);
    
    for(int i = 0; i < it->count; i++)
    {
        b[i].position.X += b[i].velocity.X;
        b[i].position.Y += b[i].velocity.Y;
    }
}
