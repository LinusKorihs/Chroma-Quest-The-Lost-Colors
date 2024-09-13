#pragma once

#include "GameState.h"
#include "config.h"
#include "VMouse.h"
#include <string>
#include <iostream>
#include "raylib.h"

class HudImageButton
{
public:
    Texture2D texture;
    Rectangle rec;
    std::string buttonText;
    float x;
    float y;
    float width;
    float height;

    // Constructor for HudImageButton which initializes all the variables
    HudImageButton() : texture{0}, rec{0, 0, 0, 0}, buttonText{""}, x{0}, y{0}, width{0}, height{0} {}

    static void unloadImageButton(HudImageButton& button)
    {
        button.texture.id = 0;
        button.texture = {0};
        button.buttonText = "";
        button.x = 0;
        button.y = 0;
        button.width = 0;
        button.height = 0;
        button.rec = {0, 0, 0, 0};
        UnloadTexture(button.texture);

        std::cout << "Unloaded button" << std::endl;
        std::cout << "Button texture id: " << button.texture.id << std::endl;
    }
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
    static void drawRGBBarTexture();
    static void drawSmallButton(HudImageButton& button);
    static void drawBigButton(HudImageButton& button);
    static void drawTutorial();
    static void drawImageButton(HudImageButton& button);
    static void drawJournal();
    static std::vector<HudImageButton> hudImagebuttons;
    static float health;
    static void init();
    static bool controlActive;
    static bool journalActive;
    static bool firstText;
    static bool secondText;
    static void drawTutJournal();

    static journalPhase journalPhase;


    static int gameOverCount;
    static void drawTutJournal();
};