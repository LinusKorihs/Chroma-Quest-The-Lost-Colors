#include "Configuration.h"
#include "TextureManage.h"

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

Direction ConfigNotConst::selectedPlayerKey = Direction::NONE;

Sound ConfigNotConst::playerWalkingSound;
Music ConfigNotConst::gameBackgroundMusic;
Sound ConfigNotConst::doorOpenSound;
Sound ConfigNotConst::chestOpenSound;
Sound ConfigNotConst::punchSound;
Sound ConfigNotConst::miniBossHit;
Sound ConfigNotConst::slimeDeath;
Sound ConfigNotConst::selectSound;
Sound ConfigNotConst::pickPageSound;
Sound ConfigNotConst::pressurePlateSound;
Sound ConfigNotConst::heartSound;
Sound ConfigNotConst::orbSound;


void ConfigFunction::toggleGamePause()
{
    ConfigNotConst::isGamePaused = !ConfigNotConst::isGamePaused;
}
