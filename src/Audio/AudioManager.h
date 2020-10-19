#pragma once

#include <soloud_c.h>
#include "Sound.h"

typedef struct AudioManager
{
    Soloud* soloud;
    Sound* sounds;
    int soundsCount;
} AudioManager;
