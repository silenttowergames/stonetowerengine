#pragma once

#include "AudioManager.h"
#include "../Application/ApplicationState.h"

void AudioManager_create(AudioManager* audioManager);
void AudioManager_addSounds(AudioManager* audioManager, Sound* sounds, int soundsCount);
void AudioManager_update(ApplicationState* app);
void AudioManager_focus(AssetManager* assetManager);
void AudioManager_blur(AssetManager* assetManager);

#define addSounds(audioManager, sounds) AudioManager_addSounds(audioManager, (Sound*)&sounds, sizeof(sounds) / sizeof(sounds[0]))
