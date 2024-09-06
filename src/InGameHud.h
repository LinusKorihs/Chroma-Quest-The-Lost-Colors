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
    static void drawControlBox();
    static void drawMana();
    static void drawStamina();
    static void drawRGBBarTexture();
    static void drawImageButton(HudImageButton& button);
    static std::vector<HudImageButton> hudImagebuttons;
    static float health;
    static float mana;
    static float stamina;
    static void init();
    static bool controlActive;

    static int gameOverCount;
};