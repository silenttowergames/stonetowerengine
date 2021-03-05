#pragma once

#include <flecs.h>
#include "Play.h"
#include "Sound.h"

Sound Sound_create_load(const char* key, Play play);
Sound Sound_create_speech(const char* key, const char* words, Play play);
Sound Sound_create_sfxr(const char* key, Play play);

SoundInstance* Sound_play(Sound* sound, Soloud* soloud);

void Sound_Free(Sound* sound);

#define soundPlay(key) Sound_play(*mapGet(app->assetManager.mapSound, key, Sound*), app->assetManager.audioManager.soloud)
