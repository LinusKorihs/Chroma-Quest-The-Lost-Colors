#include "Objects.h"
#include "TextureManage.h"
#include "MainCharacter.h"

int Stone::drawStone = 0;

std::vector<Stone> Stone::stoneObjects;
bool Stone::roomOne = false;
bool Stone::roomTwo = false;
bool Stone::roomThree = false;
bool Stone::roomFour = false;

Stone::Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle)
        : stonePositionX(stoneX), stonePositionY(stoneY), stoneSize(stoneSize), stoneTexture(stoneTexture),
          sourceRectangle(sourceRectangle), isMoving(false), targetX(stoneX), targetY(stoneY), startTime(0), duration(0.5f)
          {}

void Stone::draw()
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

void Stone::moveOneTile(int moveDirection, const std::vector<Rectangle>& wallRectangles, const std::vector<Rectangle>& stoneWallRectangles)
{
    if (isMoving) return; // Do not initiate another move while already moving

    float tileSize = 32.0f; // Assuming the tile size is 32 units

    startX = stonePositionX;
    startY = stonePositionY;

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            targetX = stonePositionX + tileSize;
            targetY = stonePositionY;
            break;
        case KEY_LEFT:
        case KEY_A:
            targetX = stonePositionX - tileSize;
            targetY = stonePositionY;
            break;
        case KEY_UP:
        case KEY_W:
            targetX = stonePositionX;
            targetY = stonePositionY - tileSize;
            break;
        case KEY_DOWN:
        case KEY_S:
            targetX = stonePositionX;
            targetY = stonePositionY + tileSize;
            break;
        default:
            return;
    }

    if (!checkCollisionWithWalls(targetX, targetY, wallRectangles, stoneWallRectangles) && !checkCollisionWithStones(targetX, targetY))
    {
        isMoving = true;
        startTime = GetTime(); // Record the start time of the move
    }
    else
    {
        targetX = stonePositionX;
        targetY = stonePositionY;
    }
}

void Stone::update(float deltaTime)
{
    if (isMoving)
    {
        float currentTime = GetTime();
        float elapsedTime = currentTime - startTime;

        if (elapsedTime >= duration)
        {
            stonePositionX = targetX;
            stonePositionY = targetY;
            isMoving = false;
        }
        else
        {
            float t = elapsedTime / duration;
            stonePositionX = lerp(startX, targetX, t);
            stonePositionY = lerp(startY, targetY, t);
        }
    }
}

float Stone::lerp(float start, float end, float t) const
{
    return start + t * (end - start);
}

bool Stone::checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRecs, const std::vector<Rectangle>& stoneWallRecs) const
{
    Rectangle newRec = { newX, newY, stoneSize, stoneSize };
    for (const Rectangle& wallRec : wallRecs)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return true;
        }
    }

    for (const Rectangle& stoneWallRec : stoneWallRecs)
    {
        if (CheckCollisionRecs(newRec, stoneWallRec))
        {
            return true;
        }
    }
    return false;
}

extern EnemyManager* enemyManager;

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

    for (const auto &enemy: MainCharacter::enemyManager->enemies)
    {
        if (CheckCollisionRecs(newRec, enemy->getRec()))
        {
            return true;
        }
    }
    return false;
}

void Stone::resetStones()
{
    if(roomOne)
    {
        Stone::stoneObjects[0].stonePositionX = 38*32;
        Stone::stoneObjects[0].stonePositionY = 74*32;
        Stone::stoneObjects[1].stonePositionX = 38*32;
        Stone::stoneObjects[1].stonePositionY = 75*32;
        Stone::stoneObjects[2].stonePositionX = 38*32;
        Stone::stoneObjects[2].stonePositionY = 76*32;
        Stone::stoneObjects[3].stonePositionX = 32*32;
        Stone::stoneObjects[3].stonePositionY = 74*32;
        Stone::stoneObjects[4].stonePositionX = 32*32;
        Stone::stoneObjects[4].stonePositionY = 75*32;
        Stone::stoneObjects[5].stonePositionX = 32*32;
        Stone::stoneObjects[5].stonePositionY = 76*32;
        Stone::stoneObjects[6].stonePositionX = 28*32;
        Stone::stoneObjects[6].stonePositionY = 74*32;
        Stone::stoneObjects[7].stonePositionX = 28*32;
        Stone::stoneObjects[7].stonePositionY = 76*32;
        Stone::stoneObjects[8].stonePositionX = 27*32;
        Stone::stoneObjects[8].stonePositionY = 73*32;
        Stone::stoneObjects[9].stonePositionX = 25*32;
        Stone::stoneObjects[9].stonePositionY = 73*32;
        Stone::stoneObjects[10].stonePositionX = 23*32;
        Stone::stoneObjects[10].stonePositionY = 73*32;
        Stone::stoneObjects[11].stonePositionX = 23*32;
        Stone::stoneObjects[11].stonePositionY = 75*32;
        Stone::stoneObjects[12].stonePositionX = 23*32;
        Stone::stoneObjects[12].stonePositionY = 77*32;
        Stone::stoneObjects[13].stonePositionX = 25*32;
        Stone::stoneObjects[13].stonePositionY = 77*32;
        Stone::stoneObjects[14].stonePositionX = 27*32;
        Stone::stoneObjects[14].stonePositionY = 77*32;

    }
    if(roomTwo)
    {
        Stone::stoneObjects[15].stonePositionX = 38*32;
        Stone::stoneObjects[15].stonePositionY = 57*32;
        Stone::stoneObjects[16].stonePositionX = 38*32;
        Stone::stoneObjects[16].stonePositionY = 56*32;
        Stone::stoneObjects[17].stonePositionX = 38*32;
        Stone::stoneObjects[17].stonePositionY = 55*32;
        Stone::stoneObjects[18].stonePositionX = 32*32;
        Stone::stoneObjects[18].stonePositionY = 57*32;
        Stone::stoneObjects[19].stonePositionX = 32*32;
        Stone::stoneObjects[19].stonePositionY = 56*32;
        Stone::stoneObjects[20].stonePositionX = 32*32;
        Stone::stoneObjects[20].stonePositionY = 55*32;

    }
    if(roomThree)
    {
        Stone::stoneObjects[45].stonePositionX = 30*32;
        Stone::stoneObjects[45].stonePositionY = 41*32;
        Stone::stoneObjects[46].stonePositionX = 25*32;
        Stone::stoneObjects[46].stonePositionY = 41*32;
        Stone::stoneObjects[47].stonePositionX = 20*32;
        Stone::stoneObjects[47].stonePositionY = 41*32;
        Stone::stoneObjects[48].stonePositionX = 29*32;
        Stone::stoneObjects[48].stonePositionY = 39*32;
        Stone::stoneObjects[49].stonePositionX = 23*32;
        Stone::stoneObjects[49].stonePositionY = 39*32;
        Stone::stoneObjects[50].stonePositionX = 21*32;
        Stone::stoneObjects[50].stonePositionY = 39*32;
        Stone::stoneObjects[51].stonePositionX = 16*32;
        Stone::stoneObjects[51].stonePositionY = 39*32;
        Stone::stoneObjects[52].stonePositionX = 14*32;
        Stone::stoneObjects[52].stonePositionY = 39*32;
        Stone::stoneObjects[53].stonePositionX = 15*32;
        Stone::stoneObjects[53].stonePositionY = 40*32;
        Stone::stoneObjects[54].stonePositionX = 22*32;
        Stone::stoneObjects[54].stonePositionY = 40*32;
        Stone::stoneObjects[55].stonePositionX = 17*32;
        Stone::stoneObjects[55].stonePositionY = 38*32;
        Stone::stoneObjects[56].stonePositionX = 13*32;
        Stone::stoneObjects[56].stonePositionY = 38*32;
        Stone::stoneObjects[57].stonePositionX = 31*32;
        Stone::stoneObjects[57].stonePositionY = 37*32;
        Stone::stoneObjects[58].stonePositionX = 27*32;
        Stone::stoneObjects[58].stonePositionY = 37*32;
        Stone::stoneObjects[59].stonePositionX = 24*32;
        Stone::stoneObjects[59].stonePositionY = 37*32;
        Stone::stoneObjects[60].stonePositionX = 20*32;
        Stone::stoneObjects[60].stonePositionY = 37*32;
        Stone::stoneObjects[61].stonePositionX = 14*32;
        Stone::stoneObjects[61].stonePositionY = 37*32;
        Stone::stoneObjects[62].stonePositionX = 17*32;
        Stone::stoneObjects[62].stonePositionY = 36*32;
        Stone::stoneObjects[63].stonePositionX = 15*32;
        Stone::stoneObjects[63].stonePositionY = 36*32;
        Stone::stoneObjects[64].stonePositionX = 29*32;
        Stone::stoneObjects[64].stonePositionY = 35*32;
        Stone::stoneObjects[65].stonePositionX = 16*32;
        Stone::stoneObjects[65].stonePositionY = 35*32;
        Stone::stoneObjects[66].stonePositionX = 21*32;
        Stone::stoneObjects[66].stonePositionY = 34*32;
    }

    if(roomFour)
    {
        Stone::stoneObjects[24].stonePositionX = 64*32;
        Stone::stoneObjects[24].stonePositionY = 41*32;
        Stone::stoneObjects[25].stonePositionX = 60*32;
        Stone::stoneObjects[25].stonePositionY = 41*32;
        Stone::stoneObjects[26].stonePositionX = 58*32;
        Stone::stoneObjects[26].stonePositionY = 41*32;
        Stone::stoneObjects[27].stonePositionX = 54*32;
        Stone::stoneObjects[27].stonePositionY = 41*32;
        Stone::stoneObjects[28].stonePositionX = 61*32;
        Stone::stoneObjects[28].stonePositionY = 42*32;
        Stone::stoneObjects[29].stonePositionX = 59*32;
        Stone::stoneObjects[29].stonePositionY = 42*32;
        Stone::stoneObjects[30].stonePositionX = 57*32;
        Stone::stoneObjects[30].stonePositionY = 42*32;
        Stone::stoneObjects[31].stonePositionX = 60*32;
        Stone::stoneObjects[31].stonePositionY = 40*32;
        Stone::stoneObjects[32].stonePositionX = 58*32;
        Stone::stoneObjects[32].stonePositionY = 40*32;
        Stone::stoneObjects[33].stonePositionX = 63*32;
        Stone::stoneObjects[33].stonePositionY = 39*32;
        Stone::stoneObjects[34].stonePositionX = 62*32;
        Stone::stoneObjects[34].stonePositionY = 39*32;
        Stone::stoneObjects[35].stonePositionX = 56*32;
        Stone::stoneObjects[35].stonePositionY = 39*32;
        Stone::stoneObjects[36].stonePositionX = 55*32;
        Stone::stoneObjects[36].stonePositionY = 39*32;
        Stone::stoneObjects[37].stonePositionX = 64*32;
        Stone::stoneObjects[37].stonePositionY = 38*32;
        Stone::stoneObjects[38].stonePositionX = 54*32;
        Stone::stoneObjects[38].stonePositionY = 38*32;
        Stone::stoneObjects[39].stonePositionX = 62*32;
        Stone::stoneObjects[39].stonePositionY = 37*32;
        Stone::stoneObjects[40].stonePositionX = 56*32;
        Stone::stoneObjects[40].stonePositionY = 37*32;
        Stone::stoneObjects[41].stonePositionX = 63*32;
        Stone::stoneObjects[41].stonePositionY = 36*32;
        Stone::stoneObjects[42].stonePositionX = 55*32;
        Stone::stoneObjects[42].stonePositionY = 36*32;
        Stone::stoneObjects[43].stonePositionX = 59*32;
        Stone::stoneObjects[43].stonePositionY = 35*32;
    }
}

void Stone::deleteStones()
{
    Stone::stoneObjects.clear();
}

void Stone::initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect)
{
    int multiple = 32;

    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 76, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 76, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 76, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 77, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 77, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 77, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 57, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 56, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 55, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 57, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 56, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 55, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 14, multiple * 56, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 61, multiple * 56, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 51, multiple * 55, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 64, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 60, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 58, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 54, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 61, multiple * 42, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 59, multiple * 42, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 57, multiple * 42, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 60, multiple * 40, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 58, multiple * 40, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 63, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 62, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 56, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 55, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 64, multiple * 38, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 54, multiple * 38, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 62, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 56, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 63, multiple * 36, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 55, multiple * 36, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 59, multiple * 35, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 45, multiple * 37, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 30, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 20, multiple * 41, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 21, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 16, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 14, multiple * 39, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 15, multiple * 40, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 22, multiple * 40, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 17, multiple * 38, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 13, multiple * 38, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 31, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 24, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 20, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 14, multiple * 37, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 17, multiple * 36, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 15, multiple * 36, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 35, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 16, multiple * 35, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 21, multiple * 34, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 22, multiple * 28, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 41, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 43, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 45, multiple * 10, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 11, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 43, multiple * 11, multiple, stoneTexture, stoneSourceRect);

    //test steine für bossraum
    Stone::stoneObjects.emplace_back(multiple * 40, multiple * 14, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 30, multiple * 14, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 15, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 15, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 12, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 42, multiple * 12, multiple, stoneTexture, stoneSourceRect);



}
std::vector<PressurePlate> PressurePlate::pressurePlates;

PressurePlate::PressurePlate(float x, float y, float size, Texture2D& texture, bool color)
        : platePositionX(x), platePositionY(y), plateSize(size), plateTexture(texture), pressed(false), color(color)
{
}

void PressurePlate::draw() const
{
    if(!color) {
        Texture2D plateTexture = pressed ? TextureManager::getTexture("PlatePressed") : TextureManager::getTexture(
                "PlateNormal");
        DrawTexture(plateTexture, platePositionX, platePositionY, WHITE);
    }else{
        Texture2D plateTexture = TextureManager::getTexture("RedButton");
        if(!pressed){
            DrawTextureRec(plateTexture, {0,0,32,32},{platePositionX, platePositionY}, WHITE);
        }else{
            DrawTextureRec(plateTexture, {32,0,32,32},{platePositionX, platePositionY}, WHITE);
        }
    }
}

Rectangle PressurePlate::getRectangle() const
{
    return { platePositionX +6, platePositionY +5, 19, 20 }; //hab das jetzt auf die actual größe der platte gesetzt
}

bool PressurePlate::isPressed() const
{
    return pressed;
}

bool CheckProximity(Rectangle r1, Rectangle r2, float proximity)
{
    return (fabs(r1.x - r2.x) <= proximity && fabs(r1.y - r2.y) <= proximity) ||
           (fabs(r1.x + r1.width - r2.x) <= proximity && fabs(r1.y + r1.height - r2.y) <= proximity);
}

void PressurePlate::update()
{
    // das ist jetzt die größe der Füße von dem character, damit die platte nur gedrückt wird, wenn die füße drauf sind
    Rectangle playerRect = {
            MainCharacter::playerPosX+12,
            MainCharacter::playerPosY +27,
            8,//TextureManager::getTexture("MainCharacter").width * MainCharacter::playerCharacterHitBoxScale,
            5//TextureManager::getTexture("MainCharacter").height * MainCharacter::playerCharacterHitBoxScale
    };
    //DrawRectangleLines(playerRect.x, playerRect.y, playerRect.width, playerRect.height, PINK);

    Rectangle plateRect = getRectangle();

    // Debugging prints to check the rectangles
    //std::cout << "Player Rectangle: " << playerRect.x << ", " << playerRect.y << ", " << playerRect.width << ", " << playerRect.height << std::endl;
    //std::cout << "Plate Rectangle: " << plateRect.x << ", " << plateRect.y << ", " << plateRect.width << ", " << plateRect.height << std::endl;

    if(CheckCollisionRecs(playerRect, plateRect)) //füße und richtige plate größe werden gecheckt
    {
        pressed = true;
    }
   /* if (CheckProximity(plateRect, playerRect, 8.0f))
    {
        pressed = true;
    }
    /*else //hab das auskommentiert weil die platte soll ja nur 1x drückbar sein oder?
    {
        pressed = false;
    }*/
    //drawHitboxes();
}


// Hitboxes
void PressurePlate::drawHitboxes() const
{
    Rectangle plateRect = getRectangle();
    DrawRectangleLines(plateRect.x, plateRect.y, plateRect.width, plateRect.height, RED);
}

void Stone::drawHitboxes() const
{
    Rectangle stoneRect = getRectangle();
    DrawRectangleLines(stoneRect.x, stoneRect.y, stoneRect.width, stoneRect.height, BLUE);
}

void MainCharacter::drawHitboxes() const
{
    Rectangle playerRect = getRectangle();
    DrawRectangleLines(playerRect.x, playerRect.y, playerRect.width, playerRect.height, GREEN);
}

void PressurePlate::initPlates(Texture2D &plateTexture)
{
    pressurePlates.emplace_back(800, 2400, 32, plateTexture,false);//1. raum
    pressurePlates.emplace_back(22*32, 37*32, 32, plateTexture,false);//raum links
    pressurePlates.emplace_back(59*32, 37*32, 32, plateTexture,false);//raum rechts

    pressurePlates.emplace_back(28*32, 10*32, 32, plateTexture,false); //boss links
    pressurePlates.emplace_back(40*32, 14*32, 32, plateTexture,false); // boss rechts

    pressurePlates.emplace_back(35*32, 79*32, 32, plateTexture,true); //reset 1. raum
    pressurePlates.emplace_back(35*32, 61*32, 32, plateTexture,true); //reset 2. raum
    pressurePlates.emplace_back(13*32, 41*32, 32, plateTexture,true); //reset 3. raum
    pressurePlates.emplace_back(32*32, 40*32, 32, plateTexture,true); //reset 4. raum
    pressurePlates.emplace_back(53*32, 36*32, 32, plateTexture,true); //reset 5. raum
    pressurePlates.emplace_back(61*32, 45*32, 32, plateTexture,true); //reset 5. raum


}

void PressurePlate::setPressed(bool pressed) {
    this->pressed = pressed;

}


Door::Door(int doorOp, Texture2D texture, float positionX, float positionY, int doorNum, int step)
        : doorOpen(doorOp), doorTexture(texture), doorPositionX(positionX), doorPositionY(positionY), doorNumber(doorNum), currentStep(step)
{
}

void Door::draw(float deltaTime)
{
   /* if (!animationFinished) {
        frameCounter++;
        int framesPerStep;
        if(doorNumber == 1){
            framesPerStep = 8;
        }
        else {
            framesPerStep = 20; // Anzahl Frames pro Animationsschritt
        }

        if (frameCounter >= framesPerStep) {
            currentStep++;
            frameCounter = 0;

            if (currentStep > 2) {
                currentStep = 2;
                animationFinished = true;
            }
        }

        switch (currentStep) {
            case 0:
                DrawTextureRec(doorTexture, {32, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
            case 1:
                DrawTextureRec(doorTexture, {64, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
            case 2:
                DrawTextureRec(doorTexture, {96, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
        }
    } else {

        DrawTextureRec(doorTexture, {96, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE); //das bleibt dann
    }*/
    if (!animationFinished) {
        if(doorNumber == 1){
            frameSpeed = 8;
        }
        else {
            frameSpeed = 2;
        }
        frameCounter += deltaTime * frameSpeed;

        if (frameCounter >= 1.0f) {
            frameCounter -= 1;
            currentStep++;

            if (currentStep > 2) {
                currentStep = 2;
                animationFinished = true;
            }
        }

        switch (currentStep) {
            case 0:
                DrawTextureRec(doorTexture, {32, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
            case 1:
                DrawTextureRec(doorTexture, {64, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
            case 2:
                DrawTextureRec(doorTexture, {96, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
                break;
        }
    } else {

        DrawTextureRec(doorTexture, {96, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE); //das bleibt dann
    }
}

void Door::drawNormal(float sourceX)
{
    DrawTextureRec(doorTexture, {sourceX, 0, 32, 32}, {doorPositionX, doorPositionY}, WHITE);
}

Rectangle Door::getRectangle() const
{
    if(doorOpen == 0 && doorNumber == 1)
    {
        return {doorPositionX, doorPositionY, 32, 16}; // durch 2 damit man in die halbe tür laufen kann
    }
    if(doorOpen == 0 && doorNumber == 2)
    {
        return {doorPositionX, doorPositionY +16, 32, 16}; // durch 2 damit man in die halbe tür laufen kann
    }
    if(doorOpen == 0 && doorNumber == 3)
    {
        return {doorPositionX, doorPositionY, 16, 32}; // durch 2 damit man in die halbe tür laufen kann
    }
    if(doorOpen == 0 && doorNumber == 4)
    {
        return {doorPositionX + 16, doorPositionY, 16, 32}; // durch 2 damit man in die halbe tür laufen kann
    }
    else
    {
        return {doorPositionX, doorPositionY, 32, 32}; //geschlossene tür
    }
}

bool Door::isOpen() const
{
    if(doorOpen == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Door::setOpened()
{
    doorOpen = 0;
}

std::vector<Door> Door::openDoors;

void Door::initDoors(Texture2D &doorTexture1, Texture2D &doorTexture2, Texture2D &doorTexture3, Texture2D &doorTexture4)
{
    int multiple = 32;
    openDoors.emplace_back(1, doorTexture1, 35*multiple, 68*multiple,1,0); //raum 1 tür oben
    openDoors.emplace_back(1, doorTexture1, 35*multiple, 48*multiple,1,0); //raum 2 tür oben

    openDoors.emplace_back(1, doorTexture2, 41*multiple, 75*multiple,4,0); //raum 1 tür rechts
    openDoors.emplace_back(1, doorTexture3, 45*multiple, 75*multiple,3,0); //nebenraum 1 tür links
    openDoors.emplace_back(1, doorTexture3, 12*multiple, 38*multiple,3,0); //raum 4 tür links
    openDoors.emplace_back(1, doorTexture3, 8*multiple, 38*multiple,4,0); //nebenraum 4 tür rechts
    openDoors.emplace_back(1, doorTexture2, 66*multiple, 41*multiple,4,0); //raum 5 tür rechts
    openDoors.emplace_back(0, doorTexture3, 70*multiple, 41*multiple,3,0); //nebenraum 5 tür links
    openDoors.emplace_back(1, doorTexture3, 12*multiple, 38*multiple,3,0); //nebenraum 5 tür links
    openDoors.emplace_back(0, doorTexture2, 8*multiple, 38*multiple,4,0); //nebenraum 5 tür links

    openDoors.emplace_back(0, doorTexture4, 35*multiple, 82*multiple,2,0); //raum 1 tür unten
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 64*multiple,2,0); //raum 2 tür unten
    openDoors.emplace_back(0, doorTexture4, 41*multiple, 56*multiple,4,0); //raum 2 tür rechts
    openDoors.emplace_back(0, doorTexture4, 29*multiple, 56*multiple,3,0); //raum 2 tür links
    openDoors.emplace_back(0, doorTexture4, 25*multiple, 56*multiple,4,0); //raum 3 tür rechts
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 51*multiple,1,0); //raum 3 tür oben
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 47*multiple,2,0); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture4, 34*multiple, 28*multiple,4,0); //raum 4 tür rechts (oben)
    openDoors.emplace_back(0, doorTexture4, 38*multiple, 28*multiple,3,0); //raum 4 tür links (oben)
    openDoors.emplace_back(0, doorTexture4, 48*multiple, 36*multiple,4,0); //raum 4 tür rechts (mittig)
    openDoors.emplace_back(0, doorTexture4, 45*multiple, 56*multiple,3,0); //raum 4 tür links (unten)
    openDoors.emplace_back(0, doorTexture4, 61*multiple, 51*multiple,1,0); //raum 4 tür oben (unten)
    openDoors.emplace_back(0, doorTexture4, 61*multiple, 47*multiple,2,0); //raum 5 tür unten
    openDoors.emplace_back(0, doorTexture4, 52*multiple, 36*multiple,3,0); //raum 5 tür links
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 21*multiple,2,0); //bossraum unten
    openDoors.emplace_back(1, doorTexture4, 35*multiple, 82*multiple,20,0); //raum 1 tür unten

    /*doors sorted
        openDoors.emplace_back(1, doorTexture1, 35*multiple, 68*multiple,1,0); //raum 1 tür oben
    openDoors.emplace_back(1, doorTexture4, 35*multiple, 82*multiple,2,0); //raum 1 tür unten
    openDoors.emplace_back(1, doorTexture2, 41*multiple, 75*multiple,4,0); //raum 1 tür rechts

    openDoors.emplace_back(1, doorTexture3, 45*multiple, 75*multiple,3,0); //nebenraum 1 tür links

    openDoors.emplace_back(1, doorTexture1, 35*multiple, 48*multiple,1,0); //raum 2 tür oben
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 64*multiple,2,0); //raum 2 tür unten
    openDoors.emplace_back(0, doorTexture4, 41*multiple, 56*multiple,4,0); //raum 2 tür rechts
    openDoors.emplace_back(0, doorTexture4, 29*multiple, 56*multiple,3,0); //raum 2 tür links

    openDoors.emplace_back(0, doorTexture4, 25*multiple, 56*multiple,4,0); //raum 3 tür rechts
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 51*multiple,1,0); //raum 3 tür oben

    openDoors.emplace_back(1, doorTexture3, 12*multiple, 38*multiple,3,0); //raum 4 tür links
    openDoors.emplace_back(1, doorTexture3, 8*multiple, 38*multiple,4,0); //nebenraum 4 tür rechts
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 82*multiple,2,0); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 47*multiple,2,0); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture4, 34*multiple, 28*multiple,4,0); //raum 4 tür rechts (oben)
    openDoors.emplace_back(0, doorTexture4, 38*multiple, 28*multiple,3,0); //raum 4 tür links (oben)
    openDoors.emplace_back(0, doorTexture4, 48*multiple, 36*multiple,4,0); //raum 4 tür rechts (mittig)
    openDoors.emplace_back(0, doorTexture4, 45*multiple, 56*multiple,3,0); //raum 4 tür links (unten)
    openDoors.emplace_back(0, doorTexture4, 61*multiple, 51*multiple,1,0); //raum 4 tür oben (unten)

    openDoors.emplace_back(0, doorTexture4, 61*multiple, 47*multiple,2,0); //raum 5 tür unten
    openDoors.emplace_back(0, doorTexture4, 52*multiple, 36*multiple,3,0); //raum 5 tür links
    openDoors.emplace_back(1, doorTexture2, 66*multiple, 41*multiple,4,0); //raum 5 tür rechts
    openDoors.emplace_back(0, doorTexture3, 70*multiple, 41*multiple,3,0); //nebenraum 5 tür links
    openDoors.emplace_back(1, doorTexture3, 12*multiple, 38*multiple,3,0); //nebenraum 5 tür links
    openDoors.emplace_back(0, doorTexture2, 8*multiple, 38*multiple,4,0); //nebenraum 5 tür links

    openDoors.emplace_back(0, doorTexture4, 35*multiple, 21*multiple,2,0); //bossraum unten
*/

}
std::vector<Machine> Machine::machines;

Machine::Machine(float posX, float posY, float oposX, float oposY, Texture2D texture, int step)
        : machinePositionX(posX), machinePositionY(posY), machineTexture(texture), filled(false), pickedUp(false), orbPositionX(oposX), orbPositionY(oposY), currentStep(step), animationFinished(false), frameCounter(0)
{
    machineRec = {machinePositionX, machinePositionY, 34, 34};
}

void Machine::draw()
{
    if (filled)
    {
        frameCounter++;
        int framesPerStep = 11; // Anzahl Frames pro Animationsschritt

        if (frameCounter >= framesPerStep) {
            currentStep++;
            frameCounter = 0;
        }

        if(currentStep > 3){
            currentStep = 0;
        }

        switch (currentStep)
        {
            case 0:
                DrawTextureRec(machineTexture, {0, 0, 32, 32}, {machinePositionX, machinePositionY}, WHITE);
                break;
            case 1:
                DrawTextureRec(machineTexture, {32, 0, 32, 32}, {machinePositionX, machinePositionY}, WHITE);
                break;
            case 2:
                DrawTextureRec(machineTexture, {64, 0, 32, 32}, {machinePositionX, machinePositionY}, WHITE);
                break;
            case 3:
                DrawTextureRec(machineTexture, {96, 0, 32, 32}, {machinePositionX, machinePositionY}, WHITE);
                break;
        }
    }
}

void Machine::drawOrb()
{

    if(!pickedUp)
    {
        Rectangle orbSourceRec = {0, 0, 32, 32};
        DrawTextureRec(TextureManager::getTexture("Orb"),orbSourceRec, {orbPositionX, orbPositionY}, WHITE);
    }
}

void Machine::update()
{
    if(CheckCollisionRecs(machineRec, MainCharacter::HitRec) && IsKeyPressed(KEY_E) && pickedUp)
    {
        filled = true;
    }

    orbRec = {orbPositionX +8, orbPositionY, 16, 16};
    if (CheckCollisionRecs(orbRec, MainCharacter::playerRec))
    {
        pickedUp = true;
    }
}

bool Machine::isFilled()
{
    return filled;
}

bool Machine::isPickedUp()
{
    return pickedUp;
}

std::vector<Chest> Chest::chests;

Chest::Chest(float cposX, float cposY, Texture2D texture)
{
    chestPositionX = cposX;
    chestPositionY = cposY;
    chestTexture = texture;
    opened = false;
    chestRec = {chestPositionX-4, chestPositionY-8, 40, 48};
}

void Chest::init(Texture2D chestTexture)
{
    chests.emplace_back(20*32, 75*32, chestTexture);
    chests.emplace_back(16*32, 42*32, chestTexture);
    chests.emplace_back(29*32, 37*32, chestTexture);
    chests.emplace_back(45*32, 48*32, chestTexture);
    chests.emplace_back(25*32, 14*32, chestTexture);
    chests.emplace_back(45*32, 14*32, chestTexture);
    chests.emplace_back(59*32, 34*32, chestTexture);
}

void Chest::draw()
{
    if(opened)
    {
        DrawTextureRec(chestTexture, {32, 0, 32, 32}, {chestPositionX, chestPositionY}, WHITE);
    }
    else
    {
        //DrawRectangleLines(chestRec.x,chestRec.y,chestRec.width,chestRec.height, RED);
        DrawTextureRec(chestTexture, {0, 0, 32, 32}, {chestPositionX, chestPositionY}, WHITE);
    }
}

void Chest::update()
{
    if(!opened)
    {
        if (CheckCollisionRecs(chestRec, MainCharacter::playerRec) && IsKeyPressed(KEY_E)) {
            std::cout << "Chest collision" << std::endl;
            opened = true;
            if (InGameHud::health < 4.5) {
                InGameHud::health += 1;
                return;
            }
            if (InGameHud::health == 4.5) {
                InGameHud::health += 0.5;
            }
            PlaySound(ConfigNotConst::chestOpenSound);
            if (!IsSoundPlaying(ConfigNotConst::chestOpenSound)) {
                StopSound(ConfigNotConst::chestOpenSound);
            }
        }
    }
}

std::vector<Signs> Signs::signs;
Texture2D Signs::blueDist;
Texture2D Signs::redDist;
Texture2D Signs::yellowDist;
Texture2D Signs::blueRoad;
Texture2D Signs::redRoad;
Texture2D Signs::yellowRoad;

Signs::Signs(float posX, float posY, Texture2D signtexture, Texture2D textText, bool bigSign)
        : signPositionX(posX), signPositionY(posY), bigSign(bigSign), signTexture(signtexture), textTexture(textText)
{
    //blueDist = TextureManager::getTexture("blueDist");
    redDist = TextureManager::getTexture("redDist");
    yellowDist = TextureManager::getTexture("yellowDist");
    blueRoad = TextureManager::getTexture("blueRoad");
    redRoad = TextureManager::getTexture("redRoad");
    yellowRoad = TextureManager::getTexture("yellowRoad");

    if(bigSign)
    {
        signRec = {signPositionX-4, signPositionY - 40, 40, 80};
    }
    else
    {
        signRec = {signPositionX-4, signPositionY-4, 40, 40};
    }
}

void Signs::init(Texture2D signTexture)
{
    blueDist = TextureManager::getTexture("blueDist");
    signs.emplace_back(38*32, 41*32, signTexture, blueDist, false); //blue dist
    signs.emplace_back(47*32, 33*32, signTexture, redDist, false); //redDist
    signs.emplace_back(38*32, 30*32, signTexture, yellowDist, false); // yellow dist
    signs.emplace_back(34*32, 9*32, signTexture, yellowRoad, true); // yellow road
    signs.emplace_back(17*32, 38*32, signTexture, blueRoad, true); //blue road
    signs.emplace_back(59*32, 40*32, signTexture, redRoad, true); //red road
}

void Signs::draw()
{
    if(active)
    {
        DrawTexture(signTexture, 280, 10, WHITE);
        DrawTexture(textTexture, 300, 40, WHITE);
    }
}

void Signs::update()
{
    if (CheckCollisionRecs(signRec, MainCharacter::playerRec)) {
        active = true;
    }
    else
    {
        active = false;
    }
}
