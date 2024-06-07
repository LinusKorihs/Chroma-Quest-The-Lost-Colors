#pragma once

#include "GameState.h"

class Menu
{
public:
    static int drawMainMenu(GameState& gameState);
    static void drawKeyBindingsMenu(GameState& gameState);
    static bool drawControlMenu(GameState& gameState);
    static void drawLanguageMenu(GameState& gameState);
    static bool drawSettingsMenu(GameState& gameState);
    static void drawPauseMenu(GameState& gameState);
    static int drawControllerMenu(GameState& gameState);
    static void drawVolumeSlidersMenu(GameState& gameState);
    static void drawVolumeSlidersPauseMenu(GameState &gameState);

    static void loadButtonAndKeyButtonTextures();
    static void unloadButtonAndKeyButtonTextures();
};