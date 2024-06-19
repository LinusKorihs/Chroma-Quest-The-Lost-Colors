#pragma once
#include "GameState.h"

class SetKeyBindings
{
public:
    static void drawKeyBindingsMenu(GameState &gameState);
    static void settingTheKeyButtons(GameState &gameState);
    static void resetPlayerKeyBindingState();
};