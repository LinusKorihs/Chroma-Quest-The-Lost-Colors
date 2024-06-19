#include "Audio.h"
#include "Configuration.h" // Assuming this is where ConfigNotConst is defined
#include "Menu.h"
#include "raylib.h"

int Audio::index = 0;

Rectangle Audio::updateSliderPositions(int index)
{
    Audio::index = index;
    float upMenuScreenWidth = GetScreenWidth();
    float upMenuScreenHeight = GetScreenHeight();
    float newSliderWidth = upMenuScreenWidth / 2 - 50; // Breite des Sliders basierend auf der Bildschirmbreite
    float newSliderHeight = (float)upMenuScreenHeight / 2 - 100; // Höhe des Sliders basierend auf der Bildschirmhöhe
    float startY = (upMenuScreenHeight - (3 * newSliderHeight + 2 * Menu::sliderSpacing)) / 2;

    float sliderY = startY + Audio::index * (newSliderHeight + Menu::sliderSpacing);

    return Rectangle{(upMenuScreenWidth - newSliderWidth) / 2, sliderY, newSliderWidth, newSliderHeight};
}

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
    Rectangle sliderPos = updateSliderPositions(Audio::index = 0);
    Rectangle slider = {sliderPos.x, sliderY, sliderPos.width, sliderPos.height};

    DrawRectangleLines(slider.x, slider.y, slider.width, slider.height, BLACK);
    DrawRectangle(slider.x, slider.y, *volumeLevel * (slider.width / 100), slider.height, GRAY);

    if (CheckCollisionPointRec(GetMousePosition(), slider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        *volumeLevel = (mouseX - slider.x) * 100 / slider.width;
        if (*volumeLevel < 0) *volumeLevel = 0;
        if (*volumeLevel > 100) *volumeLevel = 100;
    }

    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText(englishVolumeName, germanVolumeName), *volumeLevel),
             slider.x + slider.width / 2 - MeasureText(TextFormat("%s: %i",
                                                                  LanguageManager::getLocalizedGameText(englishVolumeName, germanVolumeName), *volumeLevel), 20) / 2,
             slider.y - 40, 20, BLACK);
}
