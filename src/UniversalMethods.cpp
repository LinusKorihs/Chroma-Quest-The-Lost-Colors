
#include "UniversalMethods.h"
//für sowas braucht man keine class sondern namespace
void UniversalMethods::updateAnimation(float deltaTime, float &frameCounter, int &currentFrame, int startFrame, int endFrame, float &frameRecX, type type)
{
    int textureWidth;
    int totalFrames;
    float framesSpeed;
    int tileWidth = 32;

    if(type == npc)
    {
        totalFrames = 4;
        textureWidth = totalFrames*tileWidth;
        framesSpeed = 6;
    }
    else if(type == enemy)
    {
        totalFrames = 24;
        textureWidth = totalFrames*tileWidth;
        framesSpeed = 6;
    }
    else if(type == player)
    {
        totalFrames = 32;
        textureWidth = totalFrames*tileWidth;
        framesSpeed = 6;
    }
    else
    {
        framesSpeed = 0;
        textureWidth = 0;
        totalFrames = 0;
    }

    frameCounter += deltaTime * framesSpeed;

    if (frameCounter >= 1.0f)
    {
        frameCounter = 0;

        currentFrame++;

        if (currentFrame > endFrame || currentFrame < startFrame)
        {
            currentFrame = startFrame;
        }

        frameRecX = (float) currentFrame * (float) textureWidth / totalFrames;
    }
}

void UniversalMethods::moveObj(Vector2& position, Vector2 speed, Direction direction, float deltaTime) {
    switch (direction) {
        case Direction::LEFT:
            position.x -= speed.x * deltaTime;
            break;
        case Direction::RIGHT:
            position.x += speed.x * deltaTime;
            break;
        case Direction::UP:
            position.y -= speed.y * deltaTime;
            break;
        case Direction::DOWN:
            position.y += speed.y * deltaTime;
            break;
        case Direction::NONE:
            break;
    }
}