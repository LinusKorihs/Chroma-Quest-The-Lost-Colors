#ifndef INGAMEHUD_H
#define INGAMEHUD_H

#include "raylib.h"
#include "ApplicationState.h"
#include <string>

struct ImageButton {
    Texture2D texture;
    Rectangle rec;
    std::string text;

};

class InGameHud {
public:
    InGameHud();
    ~InGameHud();
    static void DrawHealthBarTexture();
    static void DrawRGBBarTexture();
    static void DrawImageButton(ImageButton& button);
    static std::vector<ImageButton> buttons;
};

#endif // INGAMEHUD_H