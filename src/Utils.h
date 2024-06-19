#pragma once

#include "GameState.h"
#include "config.h"
#include "raylib.h"

class Button
{
public:
    static const int buttonWidth = 150;
    static const int buttonHeight = 30;
    static const int buttonScreenWidth = PixelGameConfig::ScreenWidth / 2 - 50;
    static int setKeyBindText;
    static int countDrawText;

    static bool checkButtonClick(Rectangle button, const char* englishText, const char* germanText);
    static void drawPromptText(const char* englishDirection, const char* germanDirection);
    static void updateAllButtonDimensions(float posX, float posY, float width, float height);
    static void updateButtonDimensions(HudImageButton &button, float posX, float posY, float width, float height);
};