#pragma once

#include "GameState.h"

class ConfigConst
{
public:
    static const int targetFPS;
    static const float playerMoveSpeed;

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
