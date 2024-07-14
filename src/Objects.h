#pragma once

#include "raylib.h"
#include <vector>

class Stone
{
public:
    Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle);

    void draw();
    Rectangle getRectangle() const;
    void moveOneTile(int moveDirection, const std::vector<Rectangle> &wallRectangles);
    void update(float deltaTime);

    static void initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect);
    static std::vector<Stone> stoneObjects;

    static bool stoneCollision;
    static int drawStone;
    void drawHitboxes() const;

private:
    float stonePositionX;
    float stonePositionY;
    float stoneSize;
    float velocityX, velocityY;
    Texture2D& stoneTexture;
    Rectangle &sourceRectangle;
    bool isMoving;
    float targetX;
    float targetY;
    float startX;
    float startY;
    float startTime;
    float duration;

    bool checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle> &wallRecs) const;
    bool checkCollisionWithStones(float newX, float newY) const;
    float lerp(float start, float end, float t) const;
}; 

class PressurePlate
{
public:
    PressurePlate(float x, float y, float size, Texture2D& texture);

    void draw() const;
    Rectangle getRectangle() const;
    bool isPressed() const;
    void update();
    void drawHitboxes() const;

private:
    float platePositionX;
    float platePositionY;
    float plateSize;
    Texture2D& plateTexture;
    bool pressed;
};

class Door
{
public:
    Door(int doorOp, Texture2D texture, float positionX, float positionY, int doorNum, int step);

    void draw();
    void drawNormal(float sourceX);
    Rectangle getRectangle() const;
    bool isOpen() const;
    void setOpened();
    static void initDoors(Texture2D& doorTexture1, Texture2D& doorTexture2, Texture2D& doorTexture3, Texture2D& doorTexture4);
    static std::vector<Door> openDoors;

private:
    int doorOpen;
    int doorNumber; //1 Up, 2 Down, 3 Left, 4 Right
    Texture2D doorTexture;
    float doorPositionX;
    float doorPositionY;
    int currentStep; // Wird verwendet, um den Animationsschritt zu verfolgen
    bool animationFinished;
    int frameCounter;
};