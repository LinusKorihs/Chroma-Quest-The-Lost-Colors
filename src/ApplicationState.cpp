#include "ApplicationState.h"

ApplicationState::Language ApplicationState::currentLanguage = ApplicationState::English;

void ApplicationState::resetKeyBindingState()
{
    isWaitingForKey = false;
    selectedKey = NONE;
}

void ApplicationState::changeState(MenuState newState)
{
    currentMenu = newState;
    menuStack.push(newState);
}

void ApplicationState::togglePause()
{
    isPaused = !isPaused;
}

const char* ApplicationState::getLocalizedText(const char* englishText, const char* germanText)
{
    if (currentLanguage == English)
    {
        return englishText;
    }
    else
    {
        return germanText;
    }
}

void ApplicationState::toggleLanguage()
{
    if (currentLanguage == English)
    {
        currentLanguage = German;
    }
    else
    {
        currentLanguage = English;
    }
}