#include "Audio.h"
#include "Configuration.h"
#include "raylib.h"

void Audio::updateAudioVolumes()
{
    float globalVolumeLevel = ConfigNotConst::globalVolumeLevel / 100.0f;
    if (globalVolumeLevel == 0)
    {
        SetSoundVolume(ConfigNotConst::playerWalkingSound, 0);
        SetMusicVolume(ConfigNotConst::gameBackgroundMusic, 0);
    }
    else
    {
        SetSoundVolume(ConfigNotConst::playerWalkingSound, globalVolumeLevel * (ConfigNotConst::soundEffectsVolumeLevel / 100.0f));
        SetMusicVolume(ConfigNotConst::gameBackgroundMusic, globalVolumeLevel * (ConfigNotConst::backgroundMusicVolumeLevel / 100.0f));
    }
}

void Audio::drawVolumeSlider(VolumeType type, int* volumeLevel, const char* englishVolumeName, const char* germanVolumeName, float sliderY)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    Rectangle slider = {(float)screenWidth/2 - 50, sliderY, 150, 30};
    DrawRectangleLines(slider.x, slider.y, slider.width, slider.height, BLACK);
    DrawRectangle(slider.x, slider.y, *volumeLevel * (slider.width / 100), slider.height, GRAY);
    if (CheckCollisionPointRec(GetMousePosition(), slider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        *volumeLevel = (mouseX - slider.x) * 100 / slider.width;
        if (*volumeLevel < 0) *volumeLevel = 0;
        if (*volumeLevel > 100) *volumeLevel = 100;
    }
    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText(englishVolumeName, germanVolumeName), *volumeLevel), slider.x + slider.width / 2 - MeasureText(TextFormat("%s: %i",
                                                                                                                                                                                  LanguageManager::getLocalizedGameText(
                                                                                                                                                                          englishVolumeName,
                                                                                                                                                                          germanVolumeName), *volumeLevel), 20) / 2, slider.y - 40, 20, BLACK);
}