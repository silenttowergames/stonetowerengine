#pragma once

#include <flecs.h>
#include "../Utilities/float2d.h"

typedef struct SoundInstance
{
    int id;
    float volume;
    float2d pan;
    float sampleRate;
    float speed;
    bool loop;
    bool pausedTimer;
    bool pausedFocus;
} SoundInstance;
