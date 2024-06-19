#include "GameState.h"

LanguageManager::Language LanguageManager::currentLanguage = LanguageManager::Language::English;

void GameState::changeGameState(MenuState newState)
{
    currentGameMenu = newState;
}

const char* LanguageManager::getLocalizedGameText(const char* englishText, const char* germanText)
{
    if (LanguageManager::currentLanguage == LanguageManager::Language::English)
    {
        return englishText;
    }
    else
    {
        return germanText;
    }
}

void LanguageManager::toggleLanguage()
{
    if (LanguageManager::currentLanguage == LanguageManager::Language::English)
    {
        LanguageManager::currentLanguage = LanguageManager::Language::German;
    }
    else
    {
        LanguageManager::currentLanguage = LanguageManager::Language::English;
    }
}