#include "../Application/ApplicationState.h"
#include "Sound.h"
#include "SoundInstanceFunctions.h"

SoundInstance SoundInstance_Create(Soloud* soloud, Sound* sound)
{
    SoundInstance soundInstance;
    memset(&soundInstance, 0, sizeof(soundInstance));
    
    soundInstance.id = Soloud_play(soloud, sound->source);
    
    return soundInstance;
}

void SoundInstance_Update(SoundInstance* soundInstance)
{
    //
}
