#pragma once
#include "raylib.h"

class UnloadResources
{
public:
    static void unloadAudio();
    static void unloadTexture();
    static void unloadButtonTextures();
    static void unloadKeyButtonTextures();
};
