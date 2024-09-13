#include "DialogBox.h"

std::vector<DialogBox> DialogBox::dialogBoxes;
Font DialogBox::font;
std::vector<std::string> DialogBox::dialog1;
std::vector<std::string> DialogBox::dialog2;
std::vector<std::string> DialogBox::dialog3;
std::vector<std::string> DialogBox::dialog4;
std::vector<std::string> DialogBox::dialog5;
std::vector<std::string> DialogBox::dialog6;
std::vector<std::string> DialogBox::dialog7;
std::vector<std::string> DialogBox::dialog8;
std::vector<std::string> DialogBox::dialog9;
std::vector<std::string> DialogBox::dialog10;
std::vector<std::string> DialogBox::dialog11;


DialogBox::DialogBox(Texture2D& dialogTexture, const std::vector<std::string>& dialog)
        : dialogText(dialog), currentLineIndex(0), active(false), dialogTexture(dialogTexture)
{
    dialog2 = { "So far so good, Aurora...\nbut this is the final floor.\nIGNIS stands guard here,\none of the three color machines.","As a color machine, it´s protected\nby shields, so you´ll need\nto disable them first.","Keep your eyes open for\npressure plates on the floor...\nmaybe they could help." };
    dialog3 = { "You´re Aurora, right?", "I´m Lily,\n nice to meet you!", "Unfortunately all my other frog\ncompanions left the city already..." };
    dialog4 = { "Hello there!", "Did you come to save us?", "I´m counting on you!"};
    dialog5 = { "The Blue Tower is out\nthat way. Be careful, Aurora,\nit´s not a place for\nbrute strength.","I´m afraid\nyou´re not ready for\nthis challenge just yet."};
    dialog6 = { "Aurora, you´re awake!\nThe visions brought you here,\ndidn´t they?","I saw them too...\nThe world is fading -\nits colors, its life.","I can feel it.\nThe Three Towers...\nthey hold the key.","But before you rush off,\nknow this:","Strength alone won´t be enough.\nEach tower will test you...\ndifferently.","Speak to REMY in the eastern\npart of town and prepare well.\nThis is only the beginning..."};
    dialog7 = { "The Red Tower lies this way.\nIt's a place where strength\nspeaks louder than words.","Don’t let the weight\nof it crush you —\nand keep pushing forward!"};
    dialog8 = { "I wouldn´t go past this point...", "It´s too dangerous there!"};
    dialog9 = { "This road will lead you\nto The Yellow Tower.\nWatch yourself, Aurora...","My conscience can't let\nyou head out this way\njust yet."};
    dialog10 = { "Aurora, hey!\nGEKKO sent you, right?","He told me you were headed\nfor The Three Towers...\nI thought my big mouse ears\ndidn´t hear right!", "They're scary places, you know...\nthe red one will test you\nboth physically and mentally.","So it's not just about\nbrute force, though you’ll need\nplenty of that.","Keep your wits sharp\nand your muscles ready.\nOh, and one more thing —","Don´t get discouraged\nif things get heavy.\nYou´re stronger than you think!","Remember,\nThe Red Tower is in the east,\noutside of town.","Just stay on the road and\nit´ll lead you right to it.\nI´ll see you there!"};
    dialog11 = { "Aurora!\nLet´s meet inside."};
}

void DialogBox::update(Vector2 playerPosition)
{

    for (int i = 0; i < dialogBoxes.size(); i++)
    {
        if (CheckCollisionRecs({MainCharacter::playerRec.x, MainCharacter::playerRec.y, 32,32}, NPC::npcs[i].getInteractRec()) && !dialogBoxes[i].active && IsKeyPressed(KEY_E))
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
        DrawText(dialogText[currentLineIndex].c_str(), 180, 185, 1, WHITE);
    }
}

bool DialogBox::isActive()
{
    return active;
}

void DialogBox::init(Texture2D mouseTexture, Texture2D frogTexture, Texture2D gekkoTexture, Texture2D owlTexture)
{
    dialog1 = { "Aurora, wait! Before you head\ndeeper into the tower, there´s\nsomething you should know...","These red blocks in here\n won´t budge on their own.","You´ll need to use the\nred energy — luckily this\nwhole tower radiates it.","Can you feel it?" };

    //font = LoadFont("assets/graphics/HUD/Fipps-Regular.otf");
    dialogBoxes.emplace_back(mouseTexture, dialog1);
    dialogBoxes.emplace_back(mouseTexture, dialog2);

    dialogBoxes.emplace_back(frogTexture, dialog3);
    dialogBoxes.emplace_back(owlTexture, dialog4);
    dialogBoxes.emplace_back(gekkoTexture, dialog5);
    dialogBoxes.emplace_back(gekkoTexture, dialog6);
    dialogBoxes.emplace_back(gekkoTexture, dialog7);
    dialogBoxes.emplace_back(gekkoTexture, dialog8);
    dialogBoxes.emplace_back(gekkoTexture, dialog9);
    dialogBoxes.emplace_back(mouseTexture, dialog10);
    dialogBoxes.emplace_back(mouseTexture, dialog11);

}

