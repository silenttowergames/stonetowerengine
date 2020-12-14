#pragma once

#include "../../Rendering/Animation.h"

typedef struct Animate
{
    char* nextAnimationKey;
    Animation* animation;
    int frame;
    float progress;
    float speed;
} Animate;
