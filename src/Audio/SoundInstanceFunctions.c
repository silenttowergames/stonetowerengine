#include "../Application/ApplicationState.h"
#include "Sound.h"
#include "SoundInstanceFunctions.h"

SoundInstance SoundInstance_CreateFull(Soloud* soloud, Sound* sound, float volume, float pan, float sampleRate, float speed, bool loop)
{
    SoundInstance soundInstance;
    memset(&soundInstance, 0, sizeof(soundInstance));
    
    soundInstance.volume = volume;
    soundInstance.pan = pan;
    soundInstance.sampleRate = sampleRate;
    soundInstance.speed = speed;
    soundInstance.loop = loop;
    
    soundInstance.id = Soloud_playEx(soloud, sound->source, soundInstance.volume, soundInstance.pan, 0, 0);
    Soloud_setRelativePlaySpeed(soloud, soundInstance.id, soundInstance.speed);
    Soloud_setLooping(soloud, soundInstance.id, soundInstance.loop ? 1 : 0);
    
    if(soundInstance.sampleRate == 0)
    {
        soundInstance.sampleRate = Soloud_getSamplerate(soloud, soundInstance.id);
    }
    else
    {
        Soloud_setSamplerate(soloud, soundInstance.id, soundInstance.sampleRate);
    }
    
    return soundInstance;
}

SoundInstance SoundInstance_Create(Soloud* soloud, Sound* sound)
{
    return SoundInstance_CreateFull(soloud, sound, 1.0f, 0.0f, 0.0f, 1.0f, false);
}

void SoundInstance_Update(ApplicationState* app, SoundInstance* soundInstance)
{
    printf("test: %1.1f\n", soundInstance->volume);
    
    Soloud_setVolume(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->volume);
    Soloud_setSamplerate(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->sampleRate);
    Soloud_setRelativePlaySpeed(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->speed);
    Soloud_setLooping(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->loop ? 1 : 0);
}
