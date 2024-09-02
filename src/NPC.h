#pragma once
#include "raylib.h"
#include <vector>
#include "TextureManage.h"
#include <iostream>
#include "UniversalMethods.h"

class NPC {
public:
    NPC(Vector2 position, Texture2D& texture);
    void draw();
    Rectangle getInteractRec();
    Rectangle getRec();
    static void init(Texture2D mouse, Texture2D frog, Texture2D owl, Texture2D gekko);
    void setNpcPos(Vector2 pos);
    void update(float deltaTime);
    Vector2 getNpcPos();

    static std::vector<NPC> npcs;

private:
    Vector2 npcPos;
    Texture2D npcText;
    Rectangle npcInteractRec;
    Rectangle npcRec;
    Rectangle frameRec;

    int currentFrame = 0;
    float framesCounter = 0;
    float framesSpeed = 6;

};

