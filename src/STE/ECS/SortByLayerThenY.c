#include "SortByLayerThenY.h"
#include "Components/Renderable.h"

int SortByLayerThenY(ecs_entity_t ea, const void* _ra, ecs_entity_t eb, const void* _rb)
{
    Renderable* ra = (Renderable*)_ra;
    Renderable* rb = (Renderable*)_rb;
    
    if(ra->renderTargetID > rb->renderTargetID)
    {
        return 1;
    }
    
    if(ra->renderTargetID < rb->renderTargetID)
    {
        return -1;
    }
    
    if(ra->layer > rb->layer)
    {
        return 1;
    }
    
    if(ra->layer < rb->layer)
    {
        return -1;
    }
    
    if(ra->depth > rb->depth)
    {
        return -1;
    }
    
    if(ra->depth < rb->depth)
    {
        return 1;
    }
    
    return 0;
}
