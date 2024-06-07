#include "Audio.h"
#include "Configuration.h"
#include "LoadResources.h"
#include "raylib.h"
#include "SetKeyBindings.h"

void LoadResources::loadAudio()
{
    InitAudioDevice(); // Initialize audio device

    ConfigNotConst::playerWalkingSound = LoadSound("assets/audio/sfx/FootSteps.wav");
    ConfigNotConst::gameBackgroundMusic = LoadMusicStream("assets/audio/tracks/TestSong.wav");

    Audio::updateAudioVolumes();
    PlayMusicStream(ConfigNotConst::gameBackgroundMusic);
}

void LoadResources::loadTextures()
{
    ConfigConst::playerMC = LoadTexture("assets/graphics/MainCharacter/MainCharacter.png");
    ConfigConst::tileSet = LoadTexture("assets/graphics/Old TileSet & TileMap/TileSet.png");
}

void LoadResources::loadButtonTextures()
{
    ConfigButton::startGameButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    ConfigButton::settingsMenuButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    ConfigButton::exitGameButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
    ConfigButton::resumeButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    ConfigButton::quitButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    ConfigButton::keyBindingsButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    ConfigButton::volumeButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    ConfigButton::controlButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    ConfigButton::languageButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
    ConfigButton::controllerButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    ConfigButton::pauseButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    ConfigButton::keyboardButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    ConfigButton::languageENButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    ConfigButton::languageDEButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
};

void LoadResources::loadKeyButtonTextures()
{
    SetKeyBindings::upKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    SetKeyBindings::downKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    SetKeyBindings::leftKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    SetKeyBindings::rightKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
};