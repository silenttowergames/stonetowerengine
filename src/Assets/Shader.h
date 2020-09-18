#pragma once

#include <flecs.h>
#include <FNA3D.h>

typedef struct Shader
{
	char* key;
    char* filename;
    FNA3D_Effect* effect;
    MOJOSHADER_effect* effectData;
    bool disabled;
    void (*update)(void*);
} Shader;

#define sctx() Shader* shader = (Shader*)_shader;
