#include "InGameHud.h"
#include <iostream>
#include "MainCharacter.h"
#include "TextureManage.h"

float InGameHud::health;
std::vector<HudImageButton> InGameHud::hudImagebuttons;
bool InGameHud::controlActive = true;

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
    Texture2D heart = TextureManager::getTexture("newHeart");
    Texture2D redOrb = TextureManager::getTexture("redOrb");
    Texture2D heartHalf = TextureManager::getTexture("newHeartHalf");

    if(health > 0){
        DrawTexture(redOrb, 19, 22, WHITE);
    }

    if(health == 5){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heart, 55, 22, WHITE);
        DrawTexture(heart, 66, 22, WHITE);
        DrawTexture(heart, 77, 22, WHITE);
    }

    if(health == 4.5){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heart, 55, 22, WHITE);
        DrawTexture(heart, 66, 22, WHITE);
        DrawTexture(heartHalf, 77, 22, WHITE);
    }

    if(health == 4){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heart, 55, 22, WHITE);
        DrawTexture(heart, 66, 22, WHITE);
    }

    if(health == 3.5){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heart, 55, 22, WHITE);
        DrawTexture(heartHalf, 66, 22, WHITE);
    }

    if(health == 3){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heart, 55, 22, WHITE);
    }

    if(health == 2.5){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
        DrawTexture(heartHalf, 55, 22, WHITE);
    }

    if(health == 2){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heart, 44, 22, WHITE);
    }

    if(health == 1.5){
        DrawTexture(heart, 33, 22, WHITE);
        DrawTexture(heartHalf, 44, 22, WHITE);
    }

    if(health == 1){
        DrawTexture(heart, 33, 22, WHITE);
    }

    if(health == 0.5){
        DrawTexture(heartHalf, 33, 22, WHITE);
    }

    if(health <= 0){
    }

}

void InGameHud::drawRGBBarTexture()
{
    /*int hudHealthBarX = 1700;
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

    DrawText(LanguageManager::getLocalizedGameText("RGB:", "RGB:"), rgbBarX, rgbBarY - 20, 20, BLACK);*/
    Texture2D hudgray = TextureManager::getTexture("grayHUD");
    DrawTexture(hudgray, -10, -20, WHITE);
}

void InGameHud::drawMana(){}

void InGameHud::drawStamina(){}

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

void InGameHud::drawControlBox() {
    if(controlActive){
        Texture2D controlBox = TextureManager::getTexture("controlBox");
        DrawTexture(controlBox, 3, 180, WHITE);
        DrawText("Press ´E´ to interact", 15, 195, 1, WHITE);
        DrawText("Press ´MOUSE LEFT´ to attack", 15, 215, 1, WHITE);
        DrawText("Press ´C´ to show/hide", 15, 235, 1, WHITE);
    }
    if(IsKeyPressed(KEY_C)){
        controlActive = !controlActive;
    }
}