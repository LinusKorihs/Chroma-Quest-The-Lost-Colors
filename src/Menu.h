#pragma once
#include "ApplicationState.h"

class Menu {
public:
    static int drawMainMenu(ApplicationState &gameState);
    static void drawKeyBindingsMenu(ApplicationState &gameState);
    static bool drawControlMenu(ApplicationState &gameState);
    static void drawLanguageMenu(ApplicationState &gameState);
    static bool drawSettingsMenu(ApplicationState &gameState);
    static void drawPauseMenu(ApplicationState &gameState);
    static int drawControllerMenu(ApplicationState &gameState);
    static void drawVolumeSlidersMenu(ApplicationState &gameState);
    static void drawVolumeSlidersPauseMenu(ApplicationState &gameState);

    static Texture2D gameStartButtonTexture;
    static Texture2D settingsButtonTexture;
    static Texture2D exitButtonTexture;
    static Texture2D resumeButtonTexture;
    static Texture2D quitButtonTexture;
    static Texture2D keyBindingsButtonTexture;
    static Texture2D volumeButtonTexture;
    static Texture2D controlButtonTexture;
    static Texture2D languageButtonTexture;
    static Texture2D controllerButtonTexture;
    static Texture2D pauseButtonTexture;
    static Texture2D keyboardButtonTexture;
    static Texture2D languageENButtonTexture;
    static Texture2D languageDEButtonTexture;
    static Texture2D upKeyButtonTexture;
    static Texture2D downKeyButtonTexture;
    static Texture2D leftKeyButtonTexture;
    static Texture2D rightKeyButtonTexture;

    static void loadTextures();
    static void unloadTextures();
};