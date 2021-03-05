#pragma once

#include "SoundInstance.h"

SoundInstance SoundInstance_Create(Soloud* soloud, Sound* sound);
void SoundInstance_Update(SoundInstance* soundInstance);
