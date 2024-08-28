
#include "NPC.h"

std::vector<NPC> NPC::npcs;

NPC::NPC(Vector2 position, Texture2D& texture)
        : npcPos(position), npcText(texture)
{
    npcRec = { npcPos.x, npcPos.y, 32, 32 };
    npcInteractRec = { npcPos.x - 3, npcPos.y - 3, 38, 38 };
}

void NPC::draw()
{
    DrawRectangleLines(npcInteractRec.x, npcInteractRec.y, npcInteractRec.width, npcInteractRec.height, RED);
    DrawTexture(npcText, npcPos.x, npcPos.y, WHITE);
}

Rectangle NPC::getInteractRec()
{
    return npcInteractRec;
}

Rectangle NPC::getRec()
{
    return npcRec;
}

void NPC::init(Texture2D mouse, Texture2D frog, Texture2D owl)
{
    npcs.emplace_back(Vector2{ 34*32, 73*32 }, mouse);
    npcs.emplace_back(Vector2{ 0*32, 0*32 }, frog);
    npcs.emplace_back(Vector2{ 0*32, 0*32 }, owl);
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
