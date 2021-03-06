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
    void (*update)(void*, void*, void*);
} Shader;

#define sctx() ApplicationState* app = (ApplicationState*)_app; RenderTarget* renderTarget = (RenderTarget*)_renderTarget; Shader* shader = (Shader*)_shader;
