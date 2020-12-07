#include "wallsFunctions.h"

walls SDLToWalls(SDL_Rect rect)
{
    walls ret;
    
    ret.left = rect.x;
    ret.right = ret.left + rect.w;
    
    ret.top = rect.y;
    ret.bottom = ret.top + rect.h;
    
    return ret;
}

float wallsInside(walls w0, walls w1)
{
    float2d ret = wallsInsisde2D(w0, w1);
    
    return (ret.X + ret.Y) / 2;
}

float2d wallsInsisde2D(walls w0, walls w1)
{
    float2d ret;
    
    float2d c0;
    c0.X = w0.left + (w0.right - w0.left);
    c0.Y = w0.top + (w0.bottom - w0.top);
    
    float2d c1;
    c1.X = w0.left + (w1.right - w1.left);
    c1.Y = w0.top + (w1.bottom - w1.top);
    
    ret.X = c0.X - c1.X;
    ret.Y = c0.Y - c1.Y;
    
    return ret;
}
