#pragma once

#include "SoundInstance.h"
#include "../Application/ApplicationState.h"

SoundInstance SoundInstance_CreateFull(ApplicationState* app, Sound* sound, float volume, float pan, float sampleRate, float speed, bool loop);
SoundInstance SoundInstance_Create(ApplicationState* app, Sound* sound);
void SoundInstance_Update(ApplicationState* app, Sound* sound, SoundInstance* soundInstance);
