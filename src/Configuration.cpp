#include "Configuration.h"

const int ConfigConst::targetFPS = 60;
const float ConfigConst::playerMoveSpeed = 2.0f;

int ConfigNotConst::globalVolumeLevel = 50;
int ConfigNotConst::backgroundMusicVolumeLevel = 0;
int ConfigNotConst::soundEffectsVolumeLevel = 50;
int ConfigNotConst::isGameRunning = 1;

bool ConfigNotConst::isGamePaused = false;
bool ConfigNotConst::isWaitingForKeyInput = false;
bool ConfigNotConst::isProgramRunning = true;
bool ConfigNotConst::shouldUnloadMeat = false;
bool ConfigNotConst::shouldUnloadFruit = false;
bool ConfigNotConst::lastDirectionLeft = false;
bool ConfigNotConst::lastDirectionUp = false;
bool ConfigNotConst::lastDirectionRight = false;
bool ConfigNotConst::lastDirectionDown = false;

Direction ConfigNotConst::selectedPlayerKey = Direction::NONE;

Sound ConfigNotConst::playerWalkingSound;
Music ConfigNotConst::gameBackgroundMusic;

Texture2D ConfigConst::tileSet;
Texture2D ConfigConst::playerMC;

Texture2D ConfigButton::startGameButtonTexture;
Texture2D ConfigButton::settingsMenuButtonTexture;
Texture2D ConfigButton::exitGameButtonTexture;
Texture2D ConfigButton::resumeButtonTexture;
Texture2D ConfigButton::quitButtonTexture;
Texture2D ConfigButton::keyBindingsButtonTexture;
Texture2D ConfigButton::volumeButtonTexture;
Texture2D ConfigButton::controlButtonTexture;
Texture2D ConfigButton::languageButtonTexture;
Texture2D ConfigButton::controllerButtonTexture;
Texture2D ConfigButton::keyboardButtonTexture;
Texture2D ConfigButton::languageENButtonTexture;
Texture2D ConfigButton::languageDEButtonTexture;
Texture2D ConfigButton::pauseButtonTexture;

void ConfigFunction::toggleGamePause()
{
    ConfigNotConst::isGamePaused = !ConfigNotConst::isGamePaused;
}
