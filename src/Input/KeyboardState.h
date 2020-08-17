#pragma once

#include <SDL2/SDL.h>
#include <flecs.h>

typedef struct KeyboardState
{
	int down[240];
	int held[240];
	SDL_KeyCode codes[240];
	char letterQueue[32];
	bool acceptingTyping;
} KeyboardState;
