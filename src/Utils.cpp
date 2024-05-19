#include "Utils.h"
#include "ApplicationState.h"

int Button::setKeyBindText = 0;
int Button::countDrawText = 0;

bool Button::CheckButtonClick(Rectangle button, const char* englishText, const char* germanText)
{
    DrawText(gameState.getLocalizedText(englishText, germanText), button.x + button.width/2 - MeasureText(gameState.getLocalizedText(englishText, germanText), 20)/2, button.y + button.height/2 - 10, 20, BLACK);
    return CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::drawPromptText(const char* englishDirection, const char* germanDirection)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    DrawText(TextFormat(gameState.getLocalizedText("Press a key to swap the %c key for the %s function.", "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), gameState.keyBindings[gameState.selectedKey], gameState.getLocalizedText(englishDirection, germanDirection)),
             screenWidth / 2 - MeasureText(TextFormat(gameState.getLocalizedText("Press a key to swap the %c key for the %s function.", "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), gameState.keyBindings[gameState.selectedKey], gameState.getLocalizedText(englishDirection, germanDirection)), 20) / 2,
             screenHeight / 2 - 150, 20, BLACK);
}