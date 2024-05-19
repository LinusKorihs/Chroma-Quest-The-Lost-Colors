#pragma once
#include "raylib.h"
#include "ApplicationState.h"

class Audio {
public:
    static void updateVolumes();
    static void loadResourcesAndInitAudio();
    static void unloadResourcesAndCloseAudio();
    static void drawVolumeSlider(VolumeType type, int* volume, const char* englishVolumeName, const char* germanVolumeName, float sliderY);
};