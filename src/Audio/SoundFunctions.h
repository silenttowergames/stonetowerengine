#pragma once

#include <flecs.h>
#include "Play.h"
#include "Sound.h"

Sound Sound_create_load(const char* key, Play play, SoundCategory category);
Sound Sound_create_speech(const char* key, const char* words, Play play, SoundCategory category);
Sound Sound_create_sfxr(const char* key, Play play, SoundCategory category);

SoundInstance* Sound_playFull(ApplicationState* app, Sound* sound, float volume, float pan, float sampleRate, float speed, bool loop);
SoundInstance* Sound_play(ApplicationState* app, Sound* sound);

void Sound_Free(Sound* sound);

#define soundPlay(key) Sound_play(app, *mapGet(app->assetManager.mapSound, key, Sound*))
#define soundPlayFull(key, ...) Sound_playFull(app, *mapGet(app->assetManager.mapSound, key, Sound*), __VA_ARGS__)
