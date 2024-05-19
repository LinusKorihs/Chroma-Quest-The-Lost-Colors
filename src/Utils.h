#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "config.h"
#include "ApplicationState.h"

class Button {
public:
    static const int buttonWidth = 150;
    static const int buttonHeight = 30;
    static const int buttonScreenWidth = PixelGameConfig::ScreenWidth / 2 - 50;
    static int setKeyBindText;
    static int countDrawText;
    static bool CheckButtonClick(Rectangle button, const char* englishText, const char* germanText);
    static void drawPromptText(const char* englishDirection, const char* germanDirection);
};

#endif // UTILS_H