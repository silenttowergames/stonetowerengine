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
