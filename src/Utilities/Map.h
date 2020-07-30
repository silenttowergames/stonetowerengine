#pragma once

typedef struct Map
{
	const char** keys;
	void* values;
	int count;
} Map;
