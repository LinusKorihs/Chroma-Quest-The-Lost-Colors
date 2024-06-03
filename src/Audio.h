#pragma once
#include "ApplicationState.h"
#include "config.h"
#include "raylib.h"


class Audio {
public:
    static void UpdateVolumes();
    static void LoadResourcesAndInitAudio();
    static void UnloadResourcesAndCloseAudio();
    static void DrawVolumeSlider(VolumeType type, int* volume, const char* englishVolumeName, const char* germanVolumeName, float sliderY);
};