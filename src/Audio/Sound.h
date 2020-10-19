#pragma once

#include <soloud_c.h>
#include "Play.h"

typedef struct Sound
{
    AudioSource* source;
    Play play;
    unsigned int instances[8];
    bool instancesPausedTimer[8];
    bool instancesPausedFocus[8];
} Sound;
