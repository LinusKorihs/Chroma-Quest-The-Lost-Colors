#include "DialogBox.h"

std::vector<DialogBox> DialogBox::dialogBoxes;
Font DialogBox::font;

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
        DrawTextureEx(dialogTexture, {110,170}, 0, 1, WHITE);
        DrawTextEx(font, dialogText[currentLineIndex].c_str(), {190, 205}, 20,2, WHITE);
    }
}

bool DialogBox::isActive() const
{
    return active;
}

void DialogBox::init(Texture2D texture)
{
    font = LoadFont("assets/graphics/HUD/Fipps-Regular.otf");
    dialogBoxes.emplace_back(Vector2{ 0, 0 }, texture, std::vector<std::string>{ "Du bist angekommen!", "Es sieht so aus,"
                                                                                                       " \nals wäre der Weg versperrt..." });
}