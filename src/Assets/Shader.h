#pragma once

#include <FNA3D.h>

typedef struct Shader
{
	const char* key;
    char* filename;
    FNA3D_Effect* effect;
    MOJOSHADER_effect* effectData;
} Shader;
