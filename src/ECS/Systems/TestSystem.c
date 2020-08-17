#include <flecs.h>
#include "TestSystem.h"

void TestSystem(ecs_iter_t* it)
{
	Body* b = ecs_column(it, Body, 1);
	
	printf("===\n");
	for(int i = 0; i < it->count; i++)
	{
		printf("%s\n", b[i].name);
	}
}
