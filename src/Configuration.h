#pragma once

#include "GameState.h"

class ConfigConst
{
public:
    static const int targetFPS;
    static const float playerMoveSpeed;

    static Texture2D tileSet;
    static Texture2D playerMC;
};

class ConfigNotConst
{
public:
    static int globalVolumeLevel;
    static int backgroundMusicVolumeLevel;
    static int soundEffectsVolumeLevel;
    static int isGameRunning;

    static bool isGamePaused;
    static bool isWaitingForKeyInput;
    static bool isProgramRunning;
    static bool shouldUnloadMeat;
    static bool shouldUnloadFruit;
    static bool lastDirectionLeft;
    static bool lastDirectionUp;
    static bool lastDirectionRight;
    static bool lastDirectionDown;

    static Direction selectedPlayerKey;

    static Sound playerWalkingSound;
    static Music gameBackgroundMusic;
};

class ConfigFunction
{
public:
    static void
    toggleGamePause();
};

class ConfigButton
{
public:
    static Texture2D startGameButtonTexture;
    static Texture2D settingsMenuButtonTexture;
    static Texture2D exitGameButtonTexture;
    static Texture2D resumeButtonTexture;
    static Texture2D quitButtonTexture;
    static Texture2D keyBindingsButtonTexture;
    static Texture2D volumeButtonTexture;
    static Texture2D controlButtonTexture;
    static Texture2D languageButtonTexture;
    static Texture2D controllerButtonTexture;
    static Texture2D pauseButtonTexture;
    static Texture2D keyboardButtonTexture;
    static Texture2D languageENButtonTexture;
    static Texture2D languageDEButtonTexture;
};

