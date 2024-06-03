#include "ApplicationState.h"
#include "config.h"
#include "InGameHud.h"
#include <iostream>

InGameHud::InGameHud()
{

}

InGameHud::~InGameHud()
{

}

void InGameHud::DrawHealthBarTexture()
{
    DrawRectangle(1700, 110, 100, 20, RED);
    DrawRectangle(1700, 110, gameState.health, 20, GRAY);
    DrawText(gameState.GetLocalizedText("Healthbar:", "Lebensbalken"), 1700, 90, 20, BLACK);
}

void InGameHud::DrawRGBBarTexture()
{
    int healthBarX = 1700;
    int healthBarY = 110;
    int healthBarWidth = 100;
    int healthBarHeight = 20;
    int somePadding = 25;

    int rectangleX = healthBarX;
    int rectangleY = healthBarY - healthBarHeight - somePadding;
    int rectangleWidth = healthBarWidth;
    int rectangleHeight = 20;

    int colorWidth = rectangleWidth / 3;

    DrawRectangle(rectangleX, rectangleY, colorWidth, rectangleHeight, RED);
    DrawRectangle(rectangleX + colorWidth, rectangleY, colorWidth, rectangleHeight, GREEN);
    DrawRectangle(rectangleX + 2 * colorWidth, rectangleY, colorWidth, rectangleHeight, BLUE);

    DrawText(gameState.GetLocalizedText("RGB:", "RGB:"), rectangleX, rectangleY - 20, 20, BLACK);
}

void InGameHud::DrawImageButton(ImageButton& button)
{
    float centerX = button.rec.x + button.rec.width / 2;
    float centerY = button.rec.y + button.rec.height / 2;

    float textureX = centerX - button.texture.width / 2;
    float textureY = centerY - button.texture.height / 2;

    DrawTextureRec(button.texture, { 0.0f, 0.0f, (float)button.texture.width, (float)button.texture.height }, { textureX, textureY }, WHITE);

    int textWidth = MeasureText(button.text.c_str(), 20);
    int textHeight = 20;

    float textX = centerX - textWidth / 2;
    float textY = centerY - textHeight / 2;

    DrawText(button.text.c_str(), textX, textY, 20, BLACK);
}
