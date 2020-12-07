#include "FlecsMapFunctions.h"

uint64_t Flecs_Map_Key(const char* key)
{
	uint32_t a = 0;
	uint32_t b = 0;
	
	hashlittle2(key, strlen(key), &a, &b);
	
	return ((uint64_t)a) + (((uint64_t)b) << 32);
}
