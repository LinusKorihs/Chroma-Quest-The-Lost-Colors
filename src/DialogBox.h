#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include "MainCharacter.h"
#include "NPC.h"

class DialogBox {
public:
    DialogBox(const Vector2& triggerPosition, Texture2D dialogTexture, const std::vector<std::string>& dialogText);
    ~DialogBox();

    void update(const Vector2& playerPosition);
    void draw();
    bool isActive() const;
    static void init(Texture2D texture);

    static std::vector<DialogBox> dialogBoxes;

private:
    Vector2 triggerPosition;          // Position, an der der Dialog ausgelöst wird
    Texture2D dialogTexture;          // Textur des Dialogfeldes
    std::vector<std::string> dialogText; // Liste der Dialogzeilen
    int currentLineIndex;             // Aktueller Index des Dialogs
    bool active;                      // Ob das Dialogfeld aktiv ist
};


