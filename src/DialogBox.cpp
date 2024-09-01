#include "DialogBox.h"

std::vector<DialogBox> DialogBox::dialogBoxes;
Font DialogBox::font;

DialogBox::DialogBox(Texture2D& dialogTexture, const std::vector<std::string>& dialog)
        : dialogText(dialog), currentLineIndex(0), active(false), dialogTexture(dialogTexture)
{
}

void DialogBox::update(Vector2 playerPosition)
{
    /*if (CheckCollisionPointRec(playerPosition, { triggerPosition.x, triggerPosition.y, 32, 32 }) && !active) {
        active = true;
    } //falls es texte gibt die kein dialog sind*/

    /*for(auto& npc : NPC::npcs)
    {
        if(CheckCollisionRecs(MainCharacter::playerRec, npc.getInteractRec()) && !active && IsKeyPressed(KEY_E))
        {
            active = true;
        }
    }//für dialoge*/

    for (int i = 0; i < dialogBoxes.size(); i++)
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, NPC::npcs[i].getInteractRec()) && !dialogBoxes[i].active && IsKeyPressed(KEY_E))
        {
            dialogBoxes[i].active = true;
            break;
        }
    }

    if (active && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentLineIndex++;
        if (currentLineIndex >= dialogText.size()) {
            active = false;
            currentLineIndex = 0;
        }
    }
}

void DialogBox::draw()
{
    if (active) {
        DrawTexture(dialogTexture, 118,170, WHITE);
        DrawText(dialogText[currentLineIndex].c_str(), 190, 205, 1, WHITE);
    }
}

bool DialogBox::isActive()
{
    return active;
}

void DialogBox::init(Texture2D mouseTexture, Texture2D frogTexture, Texture2D gekkoTexture, Texture2D owlTexture)
{
    //font = LoadFont("assets/graphics/HUD/Fipps-Regular.otf");
    dialogBoxes.emplace_back(mouseTexture, std::vector<std::string>{ "Test!", "Test...." });
    dialogBoxes.emplace_back(frogTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(owlTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "blablabla"});
    dialogBoxes.emplace_back(mouseTexture, std::vector<std::string>{ "blablabla"});
}