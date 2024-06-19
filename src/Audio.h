#pragma once

#include "GameState.h"
#include "config.h"
#include "raylib.h"

class Audio
{
public:
    static Rectangle updateSliderPositions(int index);
    static void updateAudioVolumes();
    static void drawVolumeSlider(VolumeType type, int* volumeLevel, const char* englishVolumeName, const char* germanVolumeName, float sliderY);
    static int index;
};