#include "Configuration.h"
#include "InGameHud.h"
#include "Utils.h"
#include "VMouse.h"

int Button::setKeyBindText = 0;
int Button::countDrawText = 0;

bool Button::checkButtonClick(Rectangle button, const char* englishText, const char* germanText)
{
    DrawText(LanguageManager::getLocalizedGameText(englishText, germanText), button.x + button.width / 2 - MeasureText(
            LanguageManager::getLocalizedGameText(englishText, germanText), 20) / 2, button.y + button.height / 2 - 10, 20, BLACK);
    return CheckCollisionPointRec(VMouse::pos(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::drawPromptText(const char* englishDirection, const char* germanDirection)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    DrawText(TextFormat(LanguageManager::getLocalizedGameText("Press a key to swap the %c key for the %s function.",
                                                              "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), currentGameState.playerKeyBindings[ConfigNotConst::selectedPlayerKey],
                        LanguageManager::getLocalizedGameText(englishDirection, germanDirection)),
             screenWidth / 2 - MeasureText(TextFormat(
                     LanguageManager::getLocalizedGameText("Press a key to swap the %c key for the %s function.",
                                                           "Drücke eine Taste, welche die %c Taste für die Funktion %s tauschen soll."), currentGameState.playerKeyBindings[ConfigNotConst::selectedPlayerKey],
                     LanguageManager::getLocalizedGameText(englishDirection, germanDirection)), 20) / 2,
             screenHeight / 2 - 150, 20, BLACK);
}

void Button::updateButtonDimensions(HudImageButton &button, float x, float y, float width, float height)
{
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    button.rec = {x, y, width, height};
}


