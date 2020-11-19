#include "DepthSystem.h"
#include "../Components/Body.h"
#include "../Components/Renderable.h"

void DepthSystem(ecs_iter_t* it)
{
    Body* b = ecs_column(it, Body, 1);
    Renderable* r = ecs_column(it, Renderable, 2);
    
    for(int i = 0; i < it->count; i++)
    {
        r[i].depth = -b[i].position.Y;
    }
}
