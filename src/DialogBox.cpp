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
        DrawText(dialogText[currentLineIndex].c_str(), 180, 195, 1, WHITE);
    }
}

bool DialogBox::isActive()
{
    return active;
}

void DialogBox::init(Texture2D mouseTexture, Texture2D frogTexture, Texture2D gekkoTexture, Texture2D owlTexture)
{
    //font = LoadFont("assets/graphics/HUD/Fipps-Regular.otf");
    dialogBoxes.emplace_back(mouseTexture, std::vector<std::string>{ "Hello Aurora!\nGood to see you.", "It seems like the\ndoor is closed..." });
    dialogBoxes.emplace_back(frogTexture, std::vector<std::string>{ "You´re Aurora, right?", "I´m Lily,\n nice to meet you!", "Unfortunately all my other frog\ncompanions left the city already..." });
    dialogBoxes.emplace_back(owlTexture, std::vector<std::string>{ "Hello there!", "Did you come to save us?", "I´m counting on you!"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "If you follow this road,\nyou will reach the blue tower."});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "Aurora, I expected you!", "I´m glad you´re here.", "I´m Gekko. If u need directions,\nI will be there."});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "If you follow this road,\nyou will reach the red tower."});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "I wouldn´t go past this point...", "It´s too dangerous there!"});
    dialogBoxes.emplace_back(gekkoTexture, std::vector<std::string>{ "If you follow this road,\nyou will reach the yellow tower."});
    dialogBoxes.emplace_back(mouseTexture, std::vector<std::string>{ "Aurora!", "Please come meet me at\nthe red tower...","I will wait in there."});
}