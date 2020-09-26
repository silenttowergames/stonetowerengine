#include "colorFunctions.h"

unsigned int colorU(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) + (r) + (g << 8) + (b << 16);
}

unsigned int colorToU(color c)
{
	return *((unsigned int*)&c);
}

color colorUToColor(unsigned int c)
{
    return (color){
        c,
        c >> 8,
        c >> 16,
        c >> 24,
    };
}
