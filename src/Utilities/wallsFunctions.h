#pragma once

#include <SDL2/SDL.h>
#include "float2d.h"
#include "walls.h"

walls SDLToWalls(SDL_Rect rect);
float wallsInside(walls w0, walls w1);
float2d wallsInsisde2D(walls w0, walls w1);
