#include "Configuration.h"
#include <iostream>
#include "Objects.h"
#include "TextureManage.h"

int Stone::drawStone = 0;

std::vector<Stone> Stone::stoneObjects;

Stone::Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle)
        : stonePositionX(stoneX), stonePositionY(stoneY), stoneSize(stoneSize), stoneTexture(stoneTexture), sourceRectangle(sourceRectangle), velocityX(0), velocityY(0)
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
    float speed = 2.0f; // Adjust speed as necessary

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            velocityX = speed;
            velocityY = 0;
            break;
        case KEY_LEFT:
        case KEY_A:
            velocityX = -speed;
            velocityY = 0;
            break;
        case KEY_UP:
        case KEY_W:
            velocityX = 0;
            velocityY = -speed;
            break;
        case KEY_DOWN:
        case KEY_S:
            velocityX = 0;
            velocityY = speed;
            break;
        default:
            break;
    }

    float newX = stonePositionX + velocityX;
    float newY = stonePositionY + velocityY;

    if (!checkCollisionWithWalls(newX, newY, wallRectangles) && !checkCollisionWithStones(newX, newY))
    {
        stonePositionX = newX;
        stonePositionY = newY;
    }
    else
    {
        velocityX = 0; // Stop the stone if there's a collision
        velocityY = 0;
    }
}

bool Stone::checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRecs) const
{
    Rectangle newRec = { newX, newY, stoneSize, stoneSize };
    for (const Rectangle& wallRec : wallRecs)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return true;
        }
    }
    return false;
}

bool Stone::checkCollisionWithStones(float newX, float newY) const
{
    Rectangle newRec = { newX, newY, stoneSize, stoneSize };
    for (const Stone& otherStone : Stone::stoneObjects)
    {
        if (&otherStone != this && CheckCollisionRecs(newRec, otherStone.getRectangle()))
        {
            return true;
        }
    }
    return false;
}

void Stone::initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect)
{
    int multiple = 32;
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 30, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 64, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 63, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 65, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 64, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 26, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 26, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 63, multiple, stoneTexture, stoneSourceRect);
}

