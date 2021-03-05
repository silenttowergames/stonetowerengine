#pragma once

#include <flecs.h>
#include <soloud_c.h>
#include "Play.h"
#include "SoundInstance.h"

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
    SoundInstance instances[8];
    const char* key;
    char* filename;
    SoundType type;
} Sound;
