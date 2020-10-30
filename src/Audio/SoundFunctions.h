#pragma once

#include <flecs.h>
#include "Play.h"
#include "Sound.h"

Sound Sound_create_load(const char* key, Play play);
Sound Sound_create_speech(const char* key, const char* words, Play play);
Sound Sound_create_sfxr(const char* key, Play play);

bool Sound_play(Sound* sound, Soloud* soloud);