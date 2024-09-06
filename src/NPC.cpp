
#include "NPC.h"

std::vector<NPC> NPC::npcs;

NPC::NPC(Vector2 position, Texture2D& texture)
        : npcPos(position), npcText(texture)
{
    npcRec = { npcPos.x+3, npcPos.y, 26, 32 };
    npcInteractRec = { npcPos.x - 3, npcPos.y - 3, 38, 38 };
    frameRec = {0, 0, (float)npcText.width / 4, (float)npcText.height};
}

void NPC::draw()
{
    //DrawRectangleLines(npcInteractRec.x, npcInteractRec.y, npcInteractRec.width, npcInteractRec.height, RED);
    DrawTextureRec(npcText, frameRec,{npcPos.x, npcPos.y}, WHITE);
}

Rectangle NPC::getInteractRec()
{
    return npcInteractRec;
}

Rectangle NPC::getRec()
{
    return npcRec;
}

void NPC::init(Texture2D mouse, Texture2D frog, Texture2D owl, Texture2D gekko)
{
    //dungeon
    npcs.emplace_back(Vector2{ 34*32, 73*32 }, mouse);
    //overworld
    npcs.emplace_back(Vector2{ 30*32, 49*32 }, frog);
    npcs.emplace_back(Vector2{ 33*32, 17*32 }, owl);
    npcs.emplace_back(Vector2{ 16*32, 38*32 }, gekko);
    npcs.emplace_back(Vector2{ 42*32, 36*32 }, gekko);
    npcs.emplace_back(Vector2{ 60*32, 40*32 }, gekko);
    npcs.emplace_back(Vector2{ 42*32, 58*32 }, gekko);
    npcs.emplace_back(Vector2{ 37*32, 8*32 }, gekko);
    npcs.emplace_back(Vector2{ 50*32, 32*32 }, mouse);
    npcs.emplace_back(Vector2{ 113*32, 39*32 }, mouse);

}

void NPC::setNpcPos(Vector2 pos)
{
    npcPos = pos;
    npcRec = { npcPos.x, npcPos.y, 32, 32 };
    npcInteractRec = { npcPos.x - 3, npcPos.y - 3, 38, 38 };
}

Vector2 NPC::getNpcPos()
{
    return npcPos;
}

void NPC::update(float deltaTime)
{
   /* framesCounter += deltaTime * framesSpeed;

    if (framesCounter >= 1.0f) {
        framesCounter = 0;

        currentFrame++;
        if (currentFrame > 3) {
            currentFrame = 0;
        }
        frameRec.x = (float) currentFrame * (float) npcText.width / 4;
    }*/
   UniversalMethods::updateAnimation(deltaTime, framesCounter,  currentFrame, 0, 3, frameRec.x, npc);
}