#pragma once

#include "raylib.h"
#include <vector>

class Stone
{
public:
    Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle);

    void draw() const;
    void move(int moveDirection, const std::vector<Rectangle>& wallRectangles);
    static void initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect);
    Rectangle getRectangle() const;
    static int drawStone;

    static std::vector<Stone> stoneObjects;
    static bool stoneCollision;

private:
    float stonePositionX;
    float stonePositionY;
    float stoneSize;
    float velocityX, velocityY;
    Texture2D& stoneTexture;
    Rectangle &sourceRectangle;

    bool checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle> &wallRecs) const;

    bool checkCollisionWithStones(float newX, float newY) const;
};

class PressurePlate
{
public:
};

