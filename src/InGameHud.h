#pragma once

#include "GameState.h"
#include "config.h"
#include "VMouse.h"
#include <string>

struct HudImageButton
{
    Texture2D texture;
    Rectangle rec;
    std::string buttonText;
    float x;
    float y;
    float width;
    float height;
};

enum journalPhase{
    empty,
    first,
    second,
    firstAndSecond
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
    static void drawTutorial();
    static void drawImageButton(HudImageButton& button);
    static void drawJournal();
    static std::vector<HudImageButton> hudImagebuttons;
    static float health;
    static float mana;
    static float stamina;
    static void init();
    static bool controlActive;
    static bool journalActive;
    static bool firstText;
    static bool secondText;

    static journalPhase journalPhase;


    static int gameOverCount;
    static void drawTutJournal();
};