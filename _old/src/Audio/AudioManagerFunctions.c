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
            if(audioManager->sounds[i].instances[j] == 0)
            {
                continue;
            }
            
            if(Soloud_getStreamTime(audioManager->soloud, audioManager->sounds[i].instances[j]) != 0)
            {
                audioManager->sounds[i].instancesPausedTimer[j] = false;
                
                continue;
            }
            
            if(!audioManager->sounds[i].instancesPausedTimer[j])
            {
                audioManager->sounds[i].instancesPausedTimer[j] = true;
                
                continue;
            }
            
            audioManager->sounds[i].instancesPausedTimer[j] = false;
            
            if(j < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int) - 1)
            {
                int x;
                for(x = j + 1; x < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int); x++)
                {
                    audioManager->sounds[i].instances[x - 1] = audioManager->sounds[i].instances[x];
                }
                
                audioManager->sounds[i].instances[x] = 0;
            }
            else
            {
                audioManager->sounds[i].instances[j] = 0;
            }
        }
    }
}

void AudioManager_focus(AudioManager* audioManager)
{
    for(int i = 0; i < audioManager->soundsCount; i++)
    {
        for(int j = 0; j < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int); j++)
        {
            if(!audioManager->sounds[i].instancesPausedFocus[j])
            {
                continue;
            }
            
            audioManager->sounds[i].instancesPausedFocus[j] = false;
            
            Soloud_setPause(audioManager->soloud, audioManager->sounds[i].instances[j], false);
        }
    }
}

void AudioManager_blur(AudioManager* audioManager)
{
    for(int i = 0; i < audioManager->soundsCount; i++)
    {
        for(int j = 0; j < sizeof(audioManager->sounds[i].instances) / sizeof(unsigned int); j++)
        {
            if(Soloud_getPause(audioManager->soloud, audioManager->sounds[i].instances[j]))
            {
                continue;
            }
            
            audioManager->sounds[i].instancesPausedFocus[j] = true;
            
            Soloud_setPause(audioManager->soloud, audioManager->sounds[i].instances[j], true);
        }
    }
}
