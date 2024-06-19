#include "Configuration.h"
#include "UnloadResources.h"
#include "raylib.h"
#include "SetKeyBindings.h"

void UnloadResources::unloadAudio()
{
    UnloadSound(ConfigNotConst::playerWalkingSound);
    UnloadMusicStream(ConfigNotConst::gameBackgroundMusic);
    CloseAudioDevice();
}