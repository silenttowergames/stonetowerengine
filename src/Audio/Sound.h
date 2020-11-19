#pragma once

#include <flecs.h>
#include <soloud_c.h>
#include "Play.h"

typedef enum SoundType
{
    SoundType_NONE,
    SoundType_WAV,
    SoundType_SFXR,
    SoundType_SPEECH,
} SoundType;

typedef struct Sound
{
    AudioSource* source;
    Play play;
    unsigned int instances[8];
    bool instancesPausedTimer[8];
    bool instancesPausedFocus[8];
    const char* key;
    char* filename;
    SoundType type;
} Sound;
