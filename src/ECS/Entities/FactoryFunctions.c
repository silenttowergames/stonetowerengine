#include "FactoryFunctions.h"

Factory Factory_Create(const char* key, void (*callable)(ecs_world_t*, float, float))
{
    Factory factory = {
        key,
        callable,
    };
}
