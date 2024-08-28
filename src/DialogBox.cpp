#include "DialogBox.h"

std::vector<DialogBox> DialogBox::dialogBoxes;

DialogBox::DialogBox(const Vector2& triggerPos, Texture2D dialogTexture, const std::vector<std::string>& dialog)
        : triggerPosition(triggerPos), dialogText(dialog), currentLineIndex(0), active(false), dialogTexture(dialogTexture)
{
}

DialogBox::~DialogBox()
{
    UnloadTexture(dialogTexture);
}

void DialogBox::update(const Vector2& playerPosition)
{
    /*if (CheckCollisionPointRec(playerPosition, { triggerPosition.x, triggerPosition.y, 32, 32 }) && !active) {
        active = true;
    } //falls es texte gibt die kein dialog sind*/

    for(auto& npc : NPC::npcs)
    {
        if(CheckCollisionRecs(MainCharacter::playerRec, npc.getInteractRec()) && !active && IsKeyPressed(KEY_E))
        {
            active = true;
            std::cout << "Interacting with NPC" << std::endl;
        }
    }//für dialoge

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
        std::cout << "Drawing dialog box" << std::endl;
        // Zeichne die Textur des Dialogfeldes
        DrawTextureEx(dialogTexture, {33*32, 75*32}, 0, 1.5, WHITE);
       // DrawTextureEx(dialogTexture, {33*32, 75*32}, 0, 1.5, WHITE);

        // Zeichne den aktuellen Text
        DrawText(dialogText[currentLineIndex].c_str(), 1068, 2407, 1, BLACK);
        //DrawText(dialogText[currentLineIndex].c_str(), 100, 100, 1, BLACK);
    }
}

bool DialogBox::isActive() const
{
    return active;
}

void DialogBox::init(Texture2D texture)
{
   dialogBoxes.emplace_back(Vector2{ 0, 0 }, texture, std::vector<std::string>{ "Du bist angekommen!", "Es sieht so aus,"
                                                                                                       " \nals wäre der Weg versperrt..." });
}