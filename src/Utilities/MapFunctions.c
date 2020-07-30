#include "MapFunctions.h"

Map Map_Create(int size, int count, ...)
{
	Map map;
	memset(&map, 0, sizeof(Map));
	
	map.keys = malloc(sizeof(char*) * (count / 2));
	map.values = malloc(sizeof(size) * (count / 2));
	map.count = count;
	
	va_list args;
	
	va_start(args, count);
	
	int k = 0;
	int v = 0;
	for(int i = 0; i < count; i++)
	{
		if(i % 2 == 0)
		{
			// key
			map.keys[k] = va_arg(args, const char*);
			printf("%s\n", map.keys[k]);
			k++;
		}
		else
		{
			// value
			//map.values[v] = va_arg(args, void);
			va_arg(args, void*);
			v++;
		}
	}
	
	va_end(args);
	
	return map;
}

int Map_Get(Map* map, const char* key)
{
	for(int i = 0; i < map->count; i++)
	{
		if(strcmp(key, map->keys[i]) != 0)
		{
			continue;
		}
		
		return i;
	}
	
	return -1;
}
