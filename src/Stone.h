#pragma once

#include "raylib.h"
#include <vector>

class Stone
{
public:
    Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle);

    void draw() const;
    void move(int direction, const std::vector<Rectangle>& wallRectangles);
    Rectangle getRectangle() const;
    static std::vector<Stone> stoneObjects;
    static bool stoneCollision;

private:
    float stonePositionX, stonePositionY, stoneSize;
    float velocityX, velocityY;
    Texture2D& stoneTexture;
    Rectangle sourceRectangles;

    bool checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRectangles) const;
};
