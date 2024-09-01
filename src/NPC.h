#pragma once
#include "raylib.h"
#include <vector>
#include "TextureManage.h"
#include <iostream>

class NPC {
public:
    NPC(Vector2 position, Texture2D& texture);
    void draw();
    Rectangle getInteractRec();
    Rectangle getRec();
    static void init(Texture2D mouse, Texture2D frog, Texture2D owl, Texture2D gekko);
    void setNpcPos(Vector2 pos);
    void update();
    Vector2 getNpcPos();

    static std::vector<NPC> npcs;

private:
    Vector2 npcPos;
    Texture2D npcText;
    Rectangle npcInteractRec;
    Rectangle npcRec;
    Rectangle frameRec;

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 6;

};

