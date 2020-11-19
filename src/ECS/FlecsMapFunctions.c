#include "FlecsMapFunctions.h"

uint64_t Flecs_Map_Key(const char* key)
{
	return hashlittle(key, strlen(key), 0);
	
	/*
	uint32_t a, b;
	hashlittle2(key, strlen(key), &a, &b);
	uint64_t db = b;
	
	return a + (db << 32);
	//*/
}
