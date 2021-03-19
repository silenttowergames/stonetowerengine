#include "Sound.h"
#include "SoundInstanceFunctions.h"

static float SoundInstance_VolumeFormat(Config* config, Sound* sound, float volume)
{
    float mult = 0;
    
    switch(sound->category)
    {
        case SoundCategory_SFX:
        {
            mult = config->volumeSFX;
        } break;
        
        case SoundCategory_Music:
        {
            mult = config->volumeMusic;
        } break;
    }
    
    volume *= mult;
    
    volume *= config->volumeMaster;
    
    /*
    if(volume < 1)
    {
        volume = euler(volume);
    }
    */
    
    return volume;
}

SoundInstance SoundInstance_CreateFull(ApplicationState* app, Sound* sound, float volume, float pan, float sampleRate, float speed, bool loop)
{
    SoundInstance soundInstance;
    memset(&soundInstance, 0, sizeof(soundInstance));
    
    soundInstance.volume = volume;
    soundInstance.pan = pan;
    soundInstance.sampleRate = sampleRate;
    soundInstance.speed = speed;
    soundInstance.loop = loop;
    
    soundInstance.id = Soloud_playEx(app->assetManager.audioManager.soloud, sound->source, SoundInstance_VolumeFormat(&app->config, sound, volume), soundInstance.pan, 0, 0);
    Soloud_setRelativePlaySpeed(app->assetManager.audioManager.soloud, soundInstance.id, soundInstance.speed);
    Soloud_setLooping(app->assetManager.audioManager.soloud, soundInstance.id, soundInstance.loop ? 1 : 0);
    
    if(soundInstance.sampleRate == 0)
    {
        soundInstance.sampleRate = Soloud_getSamplerate(app->assetManager.audioManager.soloud, soundInstance.id);
    }
    else
    {
        Soloud_setSamplerate(app->assetManager.audioManager.soloud, soundInstance.id, soundInstance.sampleRate);
    }
    
    return soundInstance;
}

SoundInstance SoundInstance_Create(ApplicationState* app, Sound* sound)
{
    return SoundInstance_CreateFull(app, sound, 1.0f, 0.0f, 0.0f, 1.0f, false);
}

void SoundInstance_Update(ApplicationState* app, Sound* sound, SoundInstance* soundInstance)
{
    Soloud_setVolume(app->assetManager.audioManager.soloud, soundInstance->id, SoundInstance_VolumeFormat(&app->config, sound, soundInstance->volume));
    Soloud_setSamplerate(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->sampleRate);
    Soloud_setRelativePlaySpeed(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->speed);
    Soloud_setLooping(app->assetManager.audioManager.soloud, soundInstance->id, soundInstance->loop ? 1 : 0);
}
