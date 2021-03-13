#pragma once

#include <flecs.h>
#include "../Utilities/float2d.h"

typedef struct SoundInstance
{
    int id;
    float volume;
    float pan;
    float sampleRate;
    float speed;
    bool loop;
    bool pausedTimer;
    bool pausedFocus;
} SoundInstance;
