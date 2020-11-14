#include <stdlib.h>
#include <flecs.h>
#include "ArrayFunctions.h"

Array Array_Init(int length, size_t size)
{
    Array array;
    memset(&array, 0, size);
    
    array.allocated = length;
    array.length = 0;
    array.data = malloc(size * length);
    
    return array;
}

bool Array_Grow(Array* array, int length, size_t size)
{
    if(length <= array->allocated)
    {
        return false;
    }
    
    array->allocated = length;
    
    array->data = realloc(array->data, length * size);
    
    return true;
}

void Array_Free(Array* array)
{
    ecs_map_free(array->map);
    
    free(array->data);
}
