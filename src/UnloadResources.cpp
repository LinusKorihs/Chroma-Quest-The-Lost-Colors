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

void UnloadResources::unloadTexture()
{
    UnloadTexture(ConfigConst::playerMC);
    UnloadTexture(ConfigConst::tileSet);
}

void UnloadResources::unloadButtonTextures()
{
    UnloadTexture(ConfigButton::startGameButtonTexture);
    UnloadTexture(ConfigButton::settingsMenuButtonTexture);
    UnloadTexture(ConfigButton::exitGameButtonTexture);
    UnloadTexture(ConfigButton::resumeButtonTexture);
    UnloadTexture(ConfigButton::quitButtonTexture);
    UnloadTexture(ConfigButton::keyBindingsButtonTexture);
    UnloadTexture(ConfigButton::volumeButtonTexture);
    UnloadTexture(ConfigButton::controlButtonTexture);
    UnloadTexture(ConfigButton::languageButtonTexture);
    UnloadTexture(ConfigButton::controllerButtonTexture);
    UnloadTexture(ConfigButton::pauseButtonTexture);
    UnloadTexture(ConfigButton::keyboardButtonTexture);
    UnloadTexture(ConfigButton::languageENButtonTexture);
    UnloadTexture(ConfigButton::languageDEButtonTexture);
}

void UnloadResources::unloadKeyButtonTextures()
{
    UnloadTexture(SetKeyBindings::upKeyButtonTexture);
    UnloadTexture(SetKeyBindings::downKeyButtonTexture);
    UnloadTexture(SetKeyBindings::leftKeyButtonTexture);
    UnloadTexture(SetKeyBindings::rightKeyButtonTexture);
}