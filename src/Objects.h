#pragma once

#include "raylib.h"
#include <vector>
#include "InGameHud.h"
#include "Configuration.h"
#include "EnemyManager.h"

class Stone
{
public:
    Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle);

    void draw();
    Rectangle getRectangle() const;
    void moveOneTile(int moveDirection, const std::vector<Rectangle> &wallRectangles, const std::vector<Rectangle> &stoneWallRectangles, const std::vector<Rectangle>& doorRecs);
    void update(float deltaTime);

    static void initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect);
    static std::vector<Stone> stoneObjects;

    static bool stoneCollision;
    static int drawStone;
    void drawHitboxes() const;
    static void resetStones();
    static void deleteStones();

    static bool roomOne;
    static bool roomTwo;
    static bool roomThree;
    static bool roomFour;
    static bool roomFive;

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

    bool checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle> &wallRecs, const std::vector<Rectangle> &stoneWallRecs, const std::vector<Rectangle>& doorRecs) const;
    bool checkCollisionWithStones(float newX, float newY) const;
    float lerp(float start, float end, float t) const;
};

class PressurePlate
{
public:
    PressurePlate(float x, float y, float size, Texture2D& texture, int color);

    void draw() const;
    void setPressed(bool pressed);
    Rectangle getRectangle() const;
    bool isPressed() const;
    void update();
    void drawHitboxes() const;
    static void initPlates(Texture2D& plateTexture);
    static std::vector<PressurePlate> pressurePlates;

private:
    float platePositionX;
    float platePositionY;
    float plateSize;
    Texture2D& plateTexture;
    bool pressed;
    int color;
    bool redButton;
};

class Door
{
public:
    Door(int doorOp, Texture2D texture, float positionX, float positionY, int doorNum, int step);

    void draw(float deltaTime);
    void drawNormal(float sourceX);
    Rectangle getRectangle() const;
    bool isOpen() const;
    void setOpened();
    static void initDoors(Texture2D& doorTexture1, Texture2D& doorTexture2, Texture2D& doorTexture3, Texture2D& doorTexture4);
    static std::vector<Door> openDoors;

private:
    int doorOpen;
    int doorNumber; //1 Up, 2 Down, 3 Left, 4 Right,
    Texture2D doorTexture;
    float doorPositionX;
    float doorPositionY;
    int currentStep; // Wird verwendet, um den Animationsschritt zu verfolgen
    bool animationFinished;
    float frameCounter;
    float frameSpeed;
};

class Machine
{
public:
    Machine(float mposX, float mposY,float oposX, float oposY, Texture2D texture, int step);

    void draw();
    void drawOrb();
    void update();
    bool isFilled();
    bool isPickedUp();
    static std::vector<Machine> machines;

private:
    float machinePositionX;
    float machinePositionY;
    float orbPositionX;
    float orbPositionY;
    Texture2D machineTexture;
    bool filled;
    bool pickedUp;
    bool inInventory;

    Rectangle machineRec;
    Rectangle orbRec;

    int currentStep;
    bool animationFinished;
    int frameCounter;

    float frameCounterOrb;
    int currentFrameOrb;
    Rectangle frameRecOrb;
};

class Chest {
public:
    Chest(float cposX, float cposY, Texture2D texture);

    void draw();
    void update();
    static void init(Texture2D chestTexture);
    static std::vector<Chest> chests;

private:
    bool opened;
    float chestPositionX;
    float chestPositionY;
    Texture2D chestTexture;
    Rectangle chestRec;
    float frameCounter;
    int currentFrame;
    bool animationFinished;
    Rectangle frameRec;

};

class Signs {
public:
    Signs(float sposX, float sposY, Texture2D textText, bool bigSign);

    void draw();
    static void init();
    void update();
    static std::vector<Signs> signs;

private:
    float signPositionX;
    float signPositionY;
    Texture2D textTexture;
    Rectangle signRec;
    Rectangle bigSignRec;
    bool active = false;
    bool bigSign;

    static Texture2D blueRoad;
    static Texture2D redRoad;
    static Texture2D yellowRoad;
    static Texture2D blueDist;
    static Texture2D redDist;
    static Texture2D yellowDist;
    static Texture2D redTower;
};

class Journal {
public:
    Journal(float jposX, float jposY, Texture2D& texture);

    void draw();
    void update();
    static void init(Texture2D journalTexture);
    static std::vector<Journal> journals;
    Rectangle journalRec;
    bool pickedUp;

private:
    float journalPositionX;
    float journalPositionY;
    Texture2D journalTexture;
    Rectangle frameRec;
    int currentFrame;
    float frameCounter;
};