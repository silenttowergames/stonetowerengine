#pragma once

#include <flecs.h>
#include "Play.h"
#include "Sound.h"

void Sound_reset(Sound* sound, Play play);

void Sound_create_load(Sound* sound, const char* filename, Play play);
void Sound_create_speech(Sound* sound, const char* words, Play play);
void Sound_create_sfxr(Sound* sound, Play play);

bool Sound_play(Sound* sound, Soloud* soloud);
