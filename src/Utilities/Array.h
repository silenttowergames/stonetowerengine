#pragma once

typedef struct Array
{
    int length;
    int allocated;
    void* data;
    ecs_map_t* map;
} Array;
