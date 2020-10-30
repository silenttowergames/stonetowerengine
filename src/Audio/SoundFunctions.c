#include <soloud_c.h>
#include "SoundFunctions.h"

Sound Sound_create_load(const char* key, Play play)
{
    Sound sound;
    memset(&sound, 0, sizeof(Sound));
    sound.play = play;
    sound.key = key;
    
    const char* filepath = "assets/sounds/%s";
    
    sound.filename = malloc(sizeof(char*) * (strlen(filepath) + strlen(key) - 2 + 1));
    sprintf(sound.filename, filepath, key);
    
    sound.source = Wav_create();
    Wav_load(sound.source, sound.filename);
    
    return sound;
}

Sound Sound_create_speech(const char* key, const char* words, Play play)
{
    Sound sound;
    memset(&sound, 0, sizeof(Sound));
    sound.play = play;
    sound.key = key;
    
    sound.source = Speech_create();
    Speech_setText(sound.source, words);
    
    return sound;
}

Sound Sound_create_sfxr(const char* key, Play play)
{
    Sound sound;
    memset(&sound, 0, sizeof(Sound));
    sound.play = play;
    sound.key = key;
    
    sound.source = Sfxr_create();
    
    return sound;
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