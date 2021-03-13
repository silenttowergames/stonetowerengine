#pragma once

#include "SoundInstance.h"

SoundInstance SoundInstance_CreateFull(Soloud* soloud, Sound* sound, float volume, float pan, float sampleRate, float speed, bool loop);
SoundInstance SoundInstance_Create(Soloud* soloud, Sound* sound);
void SoundInstance_Update(Soloud* soloud, SoundInstance* soundInstance);
