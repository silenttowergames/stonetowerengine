#pragma once

#include "AudioManager.h"

void AudioManager_create(AudioManager* audioManager);
void AudioManager_addSounds(AudioManager* audioManager, Sound* sounds, int soundsCount);
void AudioManager_update(AudioManager* audioManager);
void AudioManager_focus(AudioManager* audioManager);
void AudioManager_blur(AudioManager* audioManager);

#define addSounds(audioManager, sounds) AudioManager_addSounds(audioManager, (Sound*)&sounds, sizeof(sounds) / sizeof(sounds[0]))
