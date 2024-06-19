#pragma once

#include "raylib.h"
#include <vector>

struct StoneData
{
    float stonePositionX;
    float stonePositionY;
    float stoneSize;
    Texture2D stoneTexture;
    Rectangle sourceRectangles;
};

class Stone
{
public:
    Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle);

    void draw() const;
    void move(int moveDirection, const std::vector<Rectangle>& wallRectangles);
    Rectangle getRectangle() const;
    static int drawStone;

    static std::vector<Stone> stoneObjects;
    static bool stoneCollision;

private:
    float stonePositionX;
    float stonePositionY;
    float stoneSize;
    Texture2D& stoneTexture;
    Rectangle &sourceRectangle;
};
