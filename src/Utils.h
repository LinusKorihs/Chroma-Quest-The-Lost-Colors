#ifndef UTILS_H
#define UTILS_H

#include "ApplicationState.h"
#include "config.h"
#include "raylib.h"



class Button {
public:
    static const int buttonWidth = 150;
    static const int buttonHeight = 30;
    static const int buttonScreenWidth = PixelGameConfig::ScreenWidth / 2 - 50;
    static int setKeyBindText;
    static int countDrawText;
    static bool CheckButtonClick(Rectangle button, const char* englishText, const char* germanText);
    static void DrawPromptText(const char* englishDirection, const char* germanDirection);
};

#endif // UTILS_H