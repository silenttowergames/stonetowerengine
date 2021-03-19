#include <string.h>
#include "AudioManagerFunctions.h"
#include "SoundInstanceFunctions.h"
#include "../Assets/AssetManager.h"

void AudioManager_create(AudioManager* audioManager)
{
    memset(audioManager, 0, sizeof(AudioManager));
    
    audioManager->soloud = Soloud_create();
    
    Soloud_init(audioManager->soloud);
    
    Soloud_setGlobalVolume(audioManager->soloud, 1.0f);
}

void AudioManager_Free(AudioManager* audioManager)
{
    Soloud_deinit(audioManager->soloud);
}

void AudioManager_addSounds(AudioManager* audioManager, Sound* sounds, int soundsCount)
{
    audioManager->sounds = sounds;
    audioManager->soundsCount = soundsCount;
}

void AudioManager_update(ApplicationState* app)
{
    for(int i = 0; i < app->assetManager.audioManager.soundsCount; i++)
    {
        for(int j = 0; j < sizeof(app->assetManager.audioManager.sounds[i].instances) / sizeof(SoundInstance); j++)
        {
            if(app->assetManager.audioManager.sounds[i].instances[j].id == 0)
            {
                continue;
            }
            
            SoundInstance_Update(app, &app->assetManager.audioManager.sounds[i], &app->assetManager.audioManager.sounds[i].instances[j]);
            
            if(Soloud_getStreamTime(app->assetManager.audioManager.soloud, app->assetManager.audioManager.sounds[i].instances[j].id) != 0)
            {
                app->assetManager.audioManager.sounds[i].instances[j].pausedTimer = false;
                
                continue;
            }
            
            if(!app->assetManager.audioManager.sounds[i].instances[j].pausedTimer)
            {
                app->assetManager.audioManager.sounds[i].instances[j].pausedTimer = true;
                
                continue;
            }
            
            app->assetManager.audioManager.sounds[i].instances[j].pausedTimer = false;
            
            if(j < sizeof(app->assetManager.audioManager.sounds[i].instances) / sizeof(SoundInstance) - 1)
            {
                int x;
                for(x = j + 1; x < sizeof(app->assetManager.audioManager.sounds[i].instances) / sizeof(SoundInstance); x++)
                {
                    app->assetManager.audioManager.sounds[i].instances[x - 1] = app->assetManager.audioManager.sounds[i].instances[x];
                }
                
                app->assetManager.audioManager.sounds[i].instances[x].id = 0;
            }
            else
            {
                app->assetManager.audioManager.sounds[i].instances[j].id = 0;
            }
        }
    }
}

void AudioManager_focus(AssetManager* assetManager)
{
    for(int i = 0; i < assetManager->lengthSound; i++)
    {
        for(int j = 0; j < sizeof(assetManager->arraySound[i].instances) / sizeof(SoundInstance); j++)
        {
            if(!assetManager->arraySound[i].instances[j].pausedFocus || !assetManager->arraySound[i].instances[j].id)
            {
                continue;
            }
            
            assetManager->arraySound[i].instances[j].pausedFocus = false;
            
            Soloud_setPause(assetManager->audioManager.soloud, assetManager->arraySound[i].instances[j].id, false);
        }
    }
}

void AudioManager_blur(AssetManager* assetManager)
{
    for(int i = 0; i < assetManager->lengthSound; i++)
    {
        for(int j = 0; j < sizeof(assetManager->arraySound[i].instances) / sizeof(SoundInstance); j++)
        {
            if(Soloud_getPause(assetManager->audioManager.soloud, assetManager->arraySound[i].instances[j].id))
            {
                continue;
            }
            
            assetManager->arraySound[i].instances[j].pausedFocus = true;
            
            Soloud_setPause(assetManager->audioManager.soloud, assetManager->arraySound[i].instances[j].id, true);
        }
    }
}
