#include <string.h>
#include "AudioManagerFunctions.h"

void AudioManager_create(AudioManager* audioManager)
{
    memset(audioManager, 0, sizeof(AudioManager));
    
    audioManager->soloud = Soloud_create();
    Soloud_setGlobalVolume(audioManager->soloud, 4);
    
    Soloud_init(audioManager->soloud);
}

void AudioManager_addSounds(AudioManager* audioManager, Sound* sounds, int soundsCount)
{
    audioManager->sounds = sounds;
    audioManager->soundsCount = soundsCount;
}

void AudioManager_update(AudioManager* audioManager)
{
    for(int i = 0; i < audioManager->soundsCount; i++)
    {
        for(int j = 0; j < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int); j++)
        {
            if(audioManager->sounds[i].instances[j].id == 0)
            {
                continue;
            }
            
            if(Soloud_getStreamTime(audioManager->soloud, audioManager->sounds[i].instances[j].id) != 0)
            {
                audioManager->sounds[i].instances[j].pausedTimer = false;
                
                continue;
            }
            
            if(!audioManager->sounds[i].instances[j].pausedTimer)
            {
                audioManager->sounds[i].instances[j].pausedTimer = true;
                
                continue;
            }
            
            audioManager->sounds[i].instances[j].pausedTimer = false;
            
            if(j < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int) - 1)
            {
                int x;
                for(x = j + 1; x < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int); x++)
                {
                    audioManager->sounds[i].instances[x - 1] = audioManager->sounds[i].instances[x];
                }
                
                audioManager->sounds[i].instances[x].id = 0;
            }
            else
            {
                audioManager->sounds[i].instances[j].id = 0;
            }
        }
    }
}

void AudioManager_focus(AssetManager* assetManager)
{
    for(int i = 0; i < assetManager->lengthSound; i++)
    {
        for(int j = 0; j < sizeof(assetManager->arraySound[i].instances) / sizeof(unsigned int); j++)
        {
            if(!assetManager->arraySound[i].instances[j].pausedFocus)
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
        for(int j = 0; j < sizeof(assetManager->arraySound[i].instances) / sizeof(unsigned int); j++)
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
