#pragma once

#include "AudioManager.h"

void AudioManager_create(AudioManager* audioManager);
void AudioManager_addSounds(AudioManager* audioManager, Sound* sounds, int soundsCount);
void AudioManager_update(AudioManager* audioManager);
void AudioManager_focus(AssetManager* assetManager);
void AudioManager_blur(AssetManager* assetManager);

#define addSounds(audioManager, sounds) AudioManager_addSounds(audioManager, (Sound*)&sounds, sizeof(sounds) / sizeof(sounds[0]))
