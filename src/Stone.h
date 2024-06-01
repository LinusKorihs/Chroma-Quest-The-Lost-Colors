#pragma once
#include "raylib.h"
#include <vector>

class Stone {
public:
    Stone(float x, float y, float size, Texture2D& texture, Rectangle& sourceRect);

    void draw() const;
    void move(int direction, const std::vector<Rectangle>& wallRecs);
    Rectangle getRectangle() const;

private:
    float x, y, size;
    float velocityX, velocityY;
    Texture2D& texture;
    Rectangle sourceRect;

    bool checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRecs) const;
};
