#include <iostream>
#include "Stone.h"
#include "LoadResources.h"

int Stone::drawStone = 0;

std::vector<Stone> Stone::stoneObjects;
bool Stone::stoneCollision;

Stone::Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle)
        : stonePositionX(stoneX), stonePositionY(stoneY), stoneSize(stoneSize), stoneTexture(stoneTexture), sourceRectangle(sourceRectangle)
{
}

void Stone::draw() const
{
    if (!IsTextureReady(TextureManager::getTexture("Stone")))
    {
        TraceLog(LOG_ERROR, "Stone texture not ready in draw function!");
        return;
    }

    sourceRectangle = {0, 0, (float)TextureManager::getTexture("Stone").width, (float)TextureManager::getTexture("Stone").height};
    DrawTextureRec(TextureManager::getTexture("Stone"), sourceRectangle, {stonePositionX, stonePositionY }, RED);
}

Rectangle Stone::getRectangle() const
{
    return {stonePositionX, stonePositionY, stoneSize, stoneSize};
}

void Stone::move(int moveDirection, const std::vector<Rectangle>& wallRectangles)
{
    float newX = stonePositionX;
    float newY = stonePositionY;

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            newX += stoneSize; // Assuming the stone moves one stoneSize
            break;
        case KEY_LEFT:
        case KEY_A:
            newX -= stoneSize;
            break;
        case KEY_UP:
        case KEY_W:
            newY -= stoneSize;
            break;
        case KEY_DOWN:
        case KEY_S:
            newY += stoneSize;
            break;
        default:
            break;
    }

    Rectangle newRec = {newX, newY, stoneSize, stoneSize};

    for (const Rectangle& wallRec : wallRectangles)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return; // Do not move if there is a collision
        }
    }

    stonePositionX = newX;
    stonePositionY = newY;
}
