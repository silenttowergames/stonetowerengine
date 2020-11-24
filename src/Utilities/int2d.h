#pragma once

typedef struct int2d
{
    int X;
    int Y;
} int2d;

#define int2dInit(x, y) (int2d){ x, y, }
