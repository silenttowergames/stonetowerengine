#include "FactoryFunctions.h"

Factory Factory_Create(const char* key, ecs_entity_t (*callable)(ecs_world_t*, float, float))
{
    Factory factory = {
        key,
        callable,
    };
}
