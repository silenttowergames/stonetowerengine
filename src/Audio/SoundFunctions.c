#include <soloud_c.h>
#include "SoundFunctions.h"

void Sound_reset(Sound* sound, Play play)
{
    memset(sound, 0, sizeof(Sound));
    
    sound->play = play;
}

void Sound_create_load(Sound* sound, const char* filename, Play play)
{
    Sound_reset(sound, play);
    
    sound->source = Wav_create();
    Wav_load(sound->source, filename);
}

void Sound_create_speech(Sound* sound, const char* words, Play play)
{
    Sound_reset(sound, play);
    
    sound->source = Speech_create();
    Speech_setText(sound->source, words);
}

void Sound_create_sfxr(Sound* sound, Play play)
{
    Sound_reset(sound, play);
    
    sound->source = Sfxr_create();
}

bool Sound_play(Sound* sound, Soloud* soloud)
{
    switch(sound->play)
    {
        case Play_Default:
        case Play_StopOne:
        {
            bool available = false;
            
            for(int i = 0; i < sizeof(sound->instances) / sizeof(unsigned int); i++)
            {
                if(sound->instances[i] != 0)
                {
                    continue;
                }
                
                available = true;
                
                int j;
                for(j = 1 + 1; j < sizeof(sound->instances) / sizeof(unsigned int); j++)
                {
                    sound->instances[j - 1] = sound->instances[j];
                }
                
                sound->instances[j - 1] = Soloud_play(soloud, sound->source);
                
                return true;
            }
            
            if(!available)
            {
                Soloud_stop(soloud, sound->instances[0]);
                
                int j;
                for(j = 1; j < sizeof(sound->instances) / sizeof(unsigned int); j++)
                {
                    sound->instances[j - 1] = sound->instances[j];
                }
                
                sound->instances[j - 1] = Soloud_play(soloud, sound->source);
                
                return true;
            }
        }
        
        case Play_StopAll:
        {
            for(int i = 0; i < sizeof(sound->instances) / sizeof(unsigned int); i++)
            {
                Soloud_stop(soloud, sound->instances[i]);
                
                sound->instances[i] = 0;
            }
            
            sound->instances[0] = Soloud_play(soloud, sound->source);
            
            return true;
        }
        
        case Play_IfAvailable:
        {
            for(int i = 0; i < sizeof(sound->instances) / sizeof(unsigned int); i++)
            {
                if(sound->instances[i] != 0)
                {
                    continue;
                }
                
                sound->instances[i] = Soloud_play(soloud, sound->source);
                
                return true;
            }
            
            return false;
        }
    }
}
