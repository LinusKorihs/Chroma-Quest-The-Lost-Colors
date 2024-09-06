#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include "MainCharacter.h"
#include "NPC.h"

class DialogBox {
public:
    DialogBox(Texture2D& dialogTexture, const std::vector<std::string>& dialogText);

    void update(Vector2 playerPosition);
    void draw();
    bool isActive();
    void setActive(bool inactive) { this->active = inactive; }
    static void init(Texture2D mouseTexture, Texture2D frogTexture, Texture2D gekkoTexture, Texture2D owlTexture);

    static std::vector<DialogBox> dialogBoxes;

private:
    Vector2 triggerPosition;
    Texture2D dialogTexture;
    std::vector<std::string> dialogText;
    int currentLineIndex;
    bool active;
    static Font font;
};


