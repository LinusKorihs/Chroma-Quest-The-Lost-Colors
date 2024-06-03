#include "ApplicationState.h"

ApplicationState::Language ApplicationState::currentLanguage = ApplicationState::English;

void ApplicationState::ResetKeyBindingState()
{
    isWaitingForKey = false;
    selectedKey = NONE;
}

void ApplicationState::ChangeState(MenuState newState)
{
    currentMenu = newState;
    menuStack.push(newState);
}

void ApplicationState::TogglePause()
{
    isPaused = !isPaused;
}

const char* ApplicationState::GetLocalizedText(const char* englishText, const char* germanText)
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

void ApplicationState::ToggleLanguage()
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