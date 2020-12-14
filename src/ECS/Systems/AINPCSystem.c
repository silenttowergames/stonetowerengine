#include <stdlib.h>
#include "AINPCSystem.h"
#include "../Components/AINPC.h"
#include "../Components/Body.h"

void AINPCSystem(ecs_iter_t* it)
{
    fctx();
	
	AINPC* a = ecs_column(it, AINPC, 1);
	Body* b = ecs_column(it, Body, 2);
    
    int _rand;
    
    for(int i = 0; i < it->count; i++)
    {
        b[i].velocity.X = 0;
        b[i].velocity.Y = 0;
        
        _rand = (rand() % 3) - 1;
        
        b[i].velocity.X += a[i].speed * _rand * fdelta();
        
        _rand = (rand() % 3) - 1;
        
        b[i].velocity.Y = a[i].speed * _rand * fdelta();
    }
}
