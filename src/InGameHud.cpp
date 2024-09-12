#include "InGameHud.h"
#include <iostream>
#include "MainCharacter.h"
#include "TextureManage.h"

float InGameHud::health;
std::vector<HudImageButton> InGameHud::hudImagebuttons;
bool InGameHud::controlActive = true;
int InGameHud::gameOverCount = 0;
bool InGameHud::journalActive = false;
journalPhase InGameHud::journalPhase = journalPhase::empty;
bool InGameHud::firstText = false;
bool InGameHud::secondText = false;

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
    /*Texture2D heart = TextureManager::getTexture("newHeart");
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
    }*/
    if(health == 5){
        DrawTexture(TextureManager::getTexture("full"), 0, 0, WHITE);
    }
    if(health == 4.5){
        DrawTexture(TextureManager::getTexture("HB4,5"), 0, 0, WHITE);
    }
    if(health == 4){
        DrawTexture(TextureManager::getTexture("HB4"), 0, 0, WHITE);
    }
    if(health == 3.5){
        DrawTexture(TextureManager::getTexture("HB3,5"), 0, 0, WHITE);
    }
    if(health == 3){
        DrawTexture(TextureManager::getTexture("HB3"), 0, 0, WHITE);
    }
    if(health == 2.5){
        DrawTexture(TextureManager::getTexture("HB2,5"), 0, 0, WHITE);
    }
    if(health == 2){
        DrawTexture(TextureManager::getTexture("HB2"), 0, 0, WHITE);
    }
    if(health == 1.5){
        DrawTexture(TextureManager::getTexture("HB1,5"), 0, 0, WHITE);
    }
    if(health == 1){
        DrawTexture(TextureManager::getTexture("HB1"), 0, 0, WHITE);
    }
    if(health == 0.5){
        DrawTexture(TextureManager::getTexture("HB0,5"), 0, 0, WHITE);
    }

    if(health <= 0){
        MainCharacter::isPlayerDead = true;
        DrawRectangle(0, 0, 2500, 3000, BLACK);
        DrawText("Game Over!", 200, 100, 20, RED);
        DrawText("Press Enter to restart", 190, 150, 1, WHITE);
        DrawText("You will respawn at the Red Tower entrance!", 140, 200, 1, WHITE);
        if(IsKeyPressed(KEY_ENTER)) {
            gameOverCount++;
            MainCharacter::playerPosX = 35*32;
            MainCharacter::playerPosY = 81*32;
            health = 5;
            PixelGame::canMove = true;
            MainCharacter::isPlayerDead = false;

        }
    }

}

void InGameHud::drawRGBBarTexture()
{
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

    }
    if(IsKeyPressed(KEY_C)){
        controlActive = !controlActive;
    }
}

void InGameHud::drawTutorial() {
    if(CheckCollisionRecs(MainCharacter::playerRec, { 34*32, 74*32, 32, 96 })){
        Texture2D redBlocks = TextureManager::getTexture("redBlocks");
        DrawTexture(redBlocks, 160, 10, WHITE);
    }
    if(CheckCollisionRecs(MainCharacter::playerRec, { 29*32, 74*32, 32, 96 })){
        Texture2D greyBlocks = TextureManager::getTexture("greyBlocks");
        DrawTexture(greyBlocks, 160, 10, WHITE);
    }
    if(CheckCollisionRecs(MainCharacter::playerRec, { 46*32, 74*32, 64, 96 })){
        Texture2D orb = TextureManager::getTexture("orb");
        DrawTexture(orb, 160, 10, WHITE);
    }
    if(CheckCollisionRecs(MainCharacter::playerRec, { 21*32, 75*32, 32, 32 })){
        Texture2D chests = TextureManager::getTexture("chests");
        DrawTexture(chests, 160, 10, WHITE);
    }
    if(CheckCollisionRecs(MainCharacter::playerRec, { 35*32, 69*32, 64, 64 })){
        Texture2D placeOrb = TextureManager::getTexture("placeOrb");
        DrawTexture(placeOrb, 160, 10, WHITE);
    }
    if(CheckCollisionRecs(MainCharacter::playerRec, { 34*32, 72*32, 96, 32 })){
        Texture2D redButton = TextureManager::getTexture("redButton");
        DrawTexture(redButton, 160, 10, WHITE);
    }
}

void InGameHud::drawJournal()
{
    if(IsKeyPressed(KEY_J))
    {
        journalActive = !journalActive;
    }

    if(journalActive)
    {
        if(journalPhase == journalPhase::empty)
        {
            Texture2D journal = TextureManager::getTexture("emptyJournal");
            DrawRectangle(0, 0, 500, 400, Fade(BLACK, 0.7f));
            DrawTexture(journal, 100, 20, WHITE);
            DrawText("nothing here", 280, 100, 1, BLACK);
        }
        if(journalPhase == journalPhase::first)
        {
            Texture2D journal = TextureManager::getTexture("page1");
            DrawRectangle(0, 0, 500, 400, Fade(BLACK, 0.7f));
            DrawTexture(journal, 100, 20, WHITE);
            DrawText("first page", 280, 100, 1, BLACK);
        }
        if(journalPhase == journalPhase::second)
        {
            Texture2D journal = TextureManager::getTexture("page2");
            DrawRectangle(0, 0, 500, 400, Fade(BLACK, 0.7f));
            DrawTexture(journal, 100, 20, WHITE);
            DrawText("second page", 280, 100, 1, BLACK);
        }
        if(journalPhase == journalPhase::firstAndSecond)
        {
            Texture2D journal = TextureManager::getTexture("page1+2");
            DrawRectangle(0, 0, 500, 400, Fade(BLACK, 0.7f));
            DrawTexture(journal, 100, 20, WHITE);
            if(CheckCollisionPointRec(VMouse::pos(), { 140, 50, 100, 15 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
               firstText = true;
               secondText = false;
            }
            if(CheckCollisionPointRec(VMouse::pos(), { 140, 70, 100, 15 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
               secondText = true;
               firstText = false;
            }
            if(firstText)
            {
                DrawText("first page", 280, 100, 1, BLACK);
            }
            if(secondText)
            {
                DrawText("second page", 280, 100, 1, BLACK);
            }
        }
    }
 }
