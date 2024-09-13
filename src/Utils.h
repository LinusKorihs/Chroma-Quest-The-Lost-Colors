#pragma once

#include "GameState.h"
#include "config.h"
#include "raylib.h"

class Button
{
public:
    static const int buttonWidthSmall = 128;
    static const int buttonHeightSmall = 48;

    static const int buttonWidthBig = 128*4;
    static const int buttonHeightBig = 48*4;
    static const int buttonScreenWidth = PixelGameConfig::ScreenWidth / 2 - 50;
    static int setKeyBindText;
    static int countDrawText;

    static bool checkButtonClick(Rectangle button, const char* englishText, const char* germanText);
    static void drawPromptText(const char* englishDirection, const char* germanDirection);
    static void updateButtonDimensions(HudImageButton &button, float posX, float posY, float width, float height);
};