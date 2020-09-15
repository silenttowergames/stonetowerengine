#include "colorFunctions.h"

unsigned int colorU(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return (a << 24) + (r << 16) + (g << 8) + b;
}

unsigned int colorToU(color c)
{
	return *((unsigned int*)&c);
}
