#pragma once

#include "FontStashFNA3D.h"

int FontStashFNA3D_RenderCreate(void* uptr, int width, int height);
int FontStashFNA3D_RenderResize(void* uptr, int width, int height);
void FontStashFNA3D_RenderUpdate(void* uptr, int* rect, const unsigned char* data);
void FontStashFNA3D_RenderDraw(void* uptr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts);
void FontStashFNA3D_RenderDelete(void* uptr);

FONScontext* FontStashFNA3D_Create(Texture* texture, int width, int height, int flags);
