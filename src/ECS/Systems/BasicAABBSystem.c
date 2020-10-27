#include "BasicAABBSystem.h"
#include "../Components/BasicAABB.h"
#include "../Components/Body.h"

ecs_query_t* aabbQuery = NULL;

void BasicAABBSystem(ecs_iter_t* it)
{
    fctx();
    
    ecs_iter_t it0 = ecs_query_iter(aabbQuery);
    ecs_iter_t it1;
    
    while(ecs_query_next(&it0))
    {
        BasicAABB* a0 = ecs_column(&it0, BasicAABB, 1);
        //
        Body* b0 = ecs_column(&it0, Body, 2);
        
        for(int i = 0; i < it0.count; i++)
        {
            b0[i].position.X += b0[i].velocity.X;
            b0[i].position.Y += b0[i].velocity.Y;
        }
    }
}
