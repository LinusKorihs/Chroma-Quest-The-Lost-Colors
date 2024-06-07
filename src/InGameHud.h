#pragma once

#include "GameState.h"
#include "config.h"
#include <string>

struct HudImageButton
{
    Texture2D texture;
    Rectangle rec;
    std::string buttonText;
};

class InGameHud
{
public:
    InGameHud();
    ~InGameHud();
    static void drawHealthBarTexture();
    static void drawRGBBarTexture();
    static void drawImageButton(HudImageButton& button);
    static std::vector<HudImageButton> hudImagebuttons;
};