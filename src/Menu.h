#pragma once

#include "GameState.h"

class Menu
{
public:
    static void updateButtonPositions(Vector2 windowSize);
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

    static void initBackgroundGif();
    static void unloadBackgroundGif();
    static void updateBackgroundAnimation();
    static void reloadBackgroundGif();

    static Image backgroundPic;
    static Texture2D backgroundTex;
private:
    static int animFrames;
    static int currentAnimFrame;
    static int frameDelay;
    static int frameCounter;

};