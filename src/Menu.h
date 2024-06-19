#pragma once

#include "GameState.h"

class Menu
{
public:
    static std::vector<float> UpdateButtonPositions();
    static int drawMainMenu(GameState &currentGameState);
    static void drawKeyBindingsMenu(GameState &currentGameState);
    static void drawControlMenu(GameState &currentGameState);
    static void drawLanguageMenu(GameState &currentGameState);
    static void drawSettingsMenu(GameState &currentGameState);
    static void drawPauseMenu(GameState &currentGameState);
    static void drawControllerMenu(GameState &currentGameState);
    static void drawVolumeSlidersMenu(GameState &currentGameState);
    static void drawVolumeSlidersPauseMenu();

    static std::vector<float> buttonPos;
    static float sliderSpacing;
};