#pragma once

#include "TextureManage.h"
#include "raylib.h"
#include "tileson.h"

class DrawMap
{
public:
    static void drawTiles(tson::Map& gameMap, Texture2D& tileTexture);
    static void drawLayer(const std::vector<unsigned int>& layer, tson::Map& map, Texture2D& tileTexture);
    static bool isWall(float x, float y);
    static bool isDoor(float x, float y);

private:
    static int sizeDoorVec;
    static int sizeWallVec;
};

