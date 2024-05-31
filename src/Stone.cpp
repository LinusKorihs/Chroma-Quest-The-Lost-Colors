#include "Stone.h"

Stone::Stone(float x, float y, float size, Texture2D& texture, Rectangle& sourceRect)
        : x(x), y(y), size(size), texture(texture), sourceRect(sourceRect), velocityX(0), velocityY(0) {}

void Stone::draw() const {
    Rectangle dest = { x, y, size, size };
    DrawTexturePro(texture, sourceRect, dest, { 0, 0 }, 0.0f, WHITE);
}

void Stone::move(int direction, const std::vector<Rectangle>& wallRecs) {
    float speed = 2.0f; // Adjust speed as necessary

    switch (direction) {
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

    float newX = x + velocityX;
    float newY = y + velocityY;

    if (!checkCollisionWithWalls(newX, newY, wallRecs)) {
        x = newX;
        y = newY;
    }
}

bool Stone::checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRecs) const {
    Rectangle newRec = { newX, newY, size, size };
    for (const Rectangle& wallRec : wallRecs) {
        if (CheckCollisionRecs(newRec, wallRec)) {
            return true;
        }
    }
    return false;
}

Rectangle Stone::getRectangle() const {
    return { x, y, size, size };
}