#include "InGameHud.h"
#include <iostream>
#include "MainCharacter.h"
#include "TextureManage.h"

float InGameHud::health;
std::vector<HudImageButton> InGameHud::hudImagebuttons;

InGameHud::InGameHud()
{

}

InGameHud::~InGameHud()
{
}

void InGameHud::init() {
    health = 5;
}
void InGameHud::drawHealthBarTexture()
{
    Texture2D heart = TextureManager::getTexture("Heart");
    Texture2D heartEmpty = TextureManager::getTexture("HeartEmpty");
    Texture2D heartHalf = TextureManager::getTexture("HeartHalf");

    if(health == 5){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heart, 40, 10, WHITE);
        DrawTexture(heart, 55, 10, WHITE);
        DrawTexture(heart, 70, 10, WHITE);
    }

    if(health == 4.5){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heart, 40, 10, WHITE);
        DrawTexture(heart, 55, 10, WHITE);
        DrawTexture(heartHalf, 70, 10, WHITE);
    }

    if(health == 4){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heart, 40, 10, WHITE);
        DrawTexture(heart, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 3.5){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heart, 40, 10, WHITE);
        DrawTexture(heartHalf, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 3){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heart, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 2.5){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heartHalf, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 2){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heart, 25, 10, WHITE);
        DrawTexture(heartEmpty, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 1.5){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heartHalf, 25, 10, WHITE);
        DrawTexture(heartEmpty, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 1){
        DrawTexture(heart, 10, 10, WHITE);
        DrawTexture(heartEmpty, 25, 10, WHITE);
        DrawTexture(heartEmpty, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health == 0.5){
        DrawTexture(heartHalf, 10, 10, WHITE);
        DrawTexture(heartEmpty, 25, 10, WHITE);
        DrawTexture(heartEmpty, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

    if(health <= 0){
        DrawTexture(heartEmpty, 10, 10, WHITE);
        DrawTexture(heartEmpty, 25, 10, WHITE);
        DrawTexture(heartEmpty, 40, 10, WHITE);
        DrawTexture(heartEmpty, 55, 10, WHITE);
        DrawTexture(heartEmpty, 70, 10, WHITE);
    }

}

void InGameHud::drawRGBBarTexture()
{
    int hudHealthBarX = 1700;
    int hudHealthBarY = 110;
    int hudHealthBarWidth = 100;
    int hudHealthBarHeight = 20;
    int hudPadding = 25;

    int rgbBarX = hudHealthBarX;
    int rgbBarY = hudHealthBarY - hudHealthBarHeight - hudPadding;
    int rgbBarWidth = hudHealthBarWidth;
    int rgbBarHeight = 20;

    int rgbBarColorWidth = rgbBarWidth / 3;

    DrawRectangle(rgbBarX, rgbBarY, rgbBarColorWidth, rgbBarHeight, RED);
    DrawRectangle(rgbBarX + rgbBarColorWidth, rgbBarY, rgbBarColorWidth, rgbBarHeight, GREEN);
    DrawRectangle(rgbBarX + 2 * rgbBarColorWidth, rgbBarY, rgbBarColorWidth, rgbBarHeight, BLUE);

    DrawText(LanguageManager::getLocalizedGameText("RGB:", "RGB:"), rgbBarX, rgbBarY - 20, 20, BLACK);
}

void InGameHud::drawImageButton(HudImageButton& button)
{
    float buttonCenterX = button.rec.x + button.rec.width / 2;
    float buttonCenterY = button.rec.y + button.rec.height / 2;

    float buttonTextureX = buttonCenterX - button.texture.width / 2;
    float buttonTextureY = buttonCenterY - button.texture.height / 2;

    DrawTextureRec(button.texture, { 0.0f, 0.0f, (float)button.texture.width, (float)button.texture.height }, {buttonTextureX, buttonTextureY }, WHITE);

    int buttonTextWidth = MeasureText(button.buttonText.c_str(), 20);
    int buttonTextHeight = 20;

    float buttonTextX = buttonCenterX - buttonTextWidth / 2;
    float buttonTextY = buttonCenterY - buttonTextHeight / 2;

    DrawText(button.buttonText.c_str(), buttonTextX, buttonTextY, 20, BLACK);
}