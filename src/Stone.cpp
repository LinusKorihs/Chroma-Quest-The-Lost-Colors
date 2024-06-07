#include "Stone.h"

Stone::Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle)
        : stonePositionX(stoneX), stonePositionY(stoneY), stoneSize(stoneSize), stoneTexture(stoneTexture), sourceRectangles(sourceRectangle), velocityX(0), velocityY(0) {}

std::vector<Stone> Stone::stoneObjects;
bool Stone::stoneCollision;

void Stone::draw() const
{
    Rectangle destination = {stonePositionX, stonePositionY, stoneSize, stoneSize };
    DrawTexturePro(stoneTexture, sourceRectangles, destination, {0, 0 }, 0.0f, WHITE);
}

void Stone::move(int direction, const std::vector<Rectangle>& wallRectangles)
{
    float speed = 2.0f; // Adjust speed as necessary

    switch (direction)
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
    }

    float newPositionX = stonePositionX + velocityX;
    float newPositionY = stonePositionY + velocityY;

    if (!checkCollisionWithWalls(newPositionX, newPositionY, wallRectangles))
    {
        stonePositionX = newPositionX;
        stonePositionY = newPositionY;
    }
}

bool Stone::checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRectangles) const
{
    Rectangle newRectangle = {newX, newY, stoneSize, stoneSize };
    for (const Rectangle& wallRectangle : wallRectangles)
    {
        if (CheckCollisionRecs(newRectangle, wallRectangle))
        {
            return true;
        }
    }
    return false;
}

Rectangle Stone::getRectangle() const
{
    return {stonePositionX, stonePositionY, stoneSize, stoneSize };
}