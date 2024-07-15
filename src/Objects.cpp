#include "Objects.h"
#include "TextureManage.h"
#include "MainCharacter.h"

int Stone::drawStone = 0;

std::vector<Stone> Stone::stoneObjects;

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

void Stone::moveOneTile(int moveDirection, const std::vector<Rectangle>& wallRectangles)
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

    if (!checkCollisionWithWalls(targetX, targetY, wallRectangles) && !checkCollisionWithStones(targetX, targetY))
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

bool Stone::checkCollisionWithWalls(float newX, float newY, const std::vector<Rectangle>& wallRecs) const
{
    Rectangle newRec = { newX, newY, stoneSize, stoneSize };
    for (const Rectangle& wallRec : wallRecs)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return true;
        }
    }
    return false;
}

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
    return false;
}

void Stone::initializeStones(Texture2D& stoneTexture, Rectangle& stoneSourceRect)
{
    int multiple = 32;
    /*Stone::stoneObjects.emplace_back(multiple * 32, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 30, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 29, multiple * 64, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 63, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 65, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 64, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 26, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 26, multiple * 63, multiple, stoneTexture, stoneSourceRect);

    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 61, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 62, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 63, multiple, stoneTexture, stoneSourceRect);*/

    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 76, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 76, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 28, multiple * 74, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 73, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 75, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 23, multiple * 77, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 25, multiple * 77, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 27, multiple * 77, multiple, stoneTexture, stoneSourceRect);

    //Stone::stoneObjects.emplace_back(multiple * 38, multiple * 57, multiple, stoneTexture, stoneSourceRect); //hab ich weggemacht damit ich türen ausprobieren kann (bin nicht durchgekommen wegen hitbox)
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 56, multiple, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 55, multiple, stoneTexture, stoneSourceRect);
   // Stone::stoneObjects.emplace_back(multiple * 32, multiple * 57, multiple, stoneTexture, stoneSourceRect);
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
    Stone::stoneObjects.emplace_back(multiple * 45, multiple * 36, multiple, stoneTexture, stoneSourceRect);
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



}

PressurePlate::PressurePlate(float x, float y, float size, Texture2D& texture)
        : platePositionX(x), platePositionY(y), plateSize(size), plateTexture(texture), pressed(false)
{
}

void PressurePlate::draw() const
{
    Texture2D plateTexture = pressed ? TextureManager::getTexture("PlatePressed") : TextureManager::getTexture("PlateNormal");
    DrawTexture(plateTexture, platePositionX, platePositionY, WHITE);
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
    DrawRectangleLines(playerRect.x, playerRect.y, playerRect.width, playerRect.height, PINK);

    Rectangle plateRect = getRectangle();

    // Debugging prints to check the rectangles
    std::cout << "Player Rectangle: " << playerRect.x << ", " << playerRect.y << ", " << playerRect.width << ", " << playerRect.height << std::endl;
    std::cout << "Plate Rectangle: " << plateRect.x << ", " << plateRect.y << ", " << plateRect.width << ", " << plateRect.height << std::endl;

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


Door::Door(int doorOp, Texture2D texture, float positionX, float positionY, int doorNum, int step)
        : doorOpen(doorOp), doorTexture(texture), doorPositionX(positionX), doorPositionY(positionY), doorNumber(doorNum), currentStep(step)
{
}

void Door::draw()
{
    if (!animationFinished) {
        frameCounter++;
        int framesPerStep = 4; // Anzahl Frames pro Animationsschritt

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

void Door::initDoors(Texture2D &doorTexture1, Texture2D &doorTexture2, Texture2D &doorTexture3, Texture2D &doorTexture4) {
    /*openDoors.emplace_back(1, doorTexture1, 1120, 1888,1); //raum 1 tür oben
    openDoors.emplace_back(1, doorTexture2, 1120, 1760,2); //raum 2 tür unten
    openDoors.emplace_back(0, doorTexture1, 992, 1632,3); //raum 2 tür links
    openDoors.emplace_back(0, doorTexture1, 864, 1632, 4); //raum 3 tür rechts
    openDoors.emplace_back(0, doorTexture1, 704, 1600, 1); //raum 3 tür oben
    openDoors.emplace_back(0, doorTexture1, 704, 1472, 2); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture1, 1024, 992, 2); //raum 4 tür rechts unten
    openDoors.emplace_back(0, doorTexture1, 1024, 1120, 1); //raum 5 tür oben
    openDoors.emplace_back(0, doorTexture1, 1344, 1184, 4); //raum 5 tür rechts
    openDoors.emplace_back(0, doorTexture1, 1472, 1184, 3); //raum 6 tür links
    openDoors.emplace_back(0, doorTexture1, 1632, 1344,2); //raum 6 tür unten
    openDoors.emplace_back(0, doorTexture1, 1632, 1472, 1); //raum 7 tür oben rechts
    openDoors.emplace_back(0, doorTexture1, 1376, 1632, 3); //raum 7 tür unten links
    openDoors.emplace_back(0, doorTexture1, 1440, 1600, 1); //raum 7 tür oben
    openDoors.emplace_back(0, doorTexture1, 1248, 1632, 4); // raum 2 tür rechts
    openDoors.emplace_back(0, doorTexture1, 1120, 1536, 1); //raum 2 tür oben
    openDoors.emplace_back(0, doorTexture1, 928, 1376, 4); //raum 3 tür rechts unten
    openDoors.emplace_back(0, doorTexture1, 1056, 1376, 3); //raum 5 tür links unten
    openDoors.emplace_back(0, doorTexture1, 1184, 1376,4); //raum 5 tür rechts unten
    openDoors.emplace_back(0, doorTexture1, 1280, 1376,3); // raum 7 tür links oben
    openDoors.emplace_back(1, doorTexture1, 1440, 1568,4); //raum 4 tür rechts umten (zu)
    openDoors.emplace_back(1, doorTexture1, 1152, 1248,1); //raum 5 tür darunter (zu)
    openDoors.emplace_back(1, doorTexture1, 1152, 1216,2); //raum 5 tür unten (zu)
    openDoors.emplace_back(0, doorTexture1, 1792, 1184,4); //raum 6 tür rechts
    openDoors.emplace_back(0, doorTexture1, 1920, 1184,3); //raum hebel rechts links
    openDoors.emplace_back(1, doorTexture1, 576, 992,3); //raum 4 tür links (zu)
    openDoors.emplace_back(1, doorTexture1, 544, 992,3); //raum 4 tür links (zu)
    openDoors.emplace_back(0, doorTexture1, 448, 1184,3); //raum 4 tür links mitte
    openDoors.emplace_back(0, doorTexture1, 320, 1184,4); //raum hebel links rechts
    openDoors.emplace_back(0, doorTexture1, 1120, 672,1); //bossraum*/
    int multiple = 32;
    openDoors.emplace_back(1, doorTexture1, 35*multiple, 68*multiple,1,0); //raum 1 tür oben
    openDoors.emplace_back(1, doorTexture2, 35*multiple, 48*multiple,1,0); //raum 2 tür oben

    openDoors.emplace_back(1, doorTexture2, 41*multiple, 75*multiple,4,0); //raum 1 tür rechts
    openDoors.emplace_back(1, doorTexture3, 45*multiple, 75*multiple,3,0); //nebenraum 1 tür links
    openDoors.emplace_back(1, doorTexture3, 12*multiple, 38*multiple,3,0); //raum 4 tür links
    openDoors.emplace_back(1, doorTexture3, 8*multiple, 38*multiple,4,0); //nebenraum 4 tür rechts
    openDoors.emplace_back(1, doorTexture3, 66*multiple, 41*multiple,4,0); //raum 5 tür rechts
    openDoors.emplace_back(1, doorTexture3, 70*multiple, 41*multiple,3,0); //nebenraum 5 tür links

    openDoors.emplace_back(0, doorTexture4, 35*multiple, 82*multiple,2,0); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 64*multiple,2,0); // raum 2 tür unten
    openDoors.emplace_back(0, doorTexture4, 41*multiple, 56*multiple,4,0); // raum 2 tür rechts
    openDoors.emplace_back(0, doorTexture4, 29*multiple, 56*multiple,3,0);//raum 2 tür links
    openDoors.emplace_back(0, doorTexture4, 25*multiple, 56*multiple,4,0);//raum 3 tür rechts
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 51*multiple,1,0);//raum 3 tür oben
    openDoors.emplace_back(0, doorTexture4, 14*multiple, 47*multiple,2,0); //raum 4 tür unten
    openDoors.emplace_back(0, doorTexture4, 34*multiple, 28*multiple,4,0); //raum 4 tür rechts (oben)
    openDoors.emplace_back(0, doorTexture4, 38*multiple, 28*multiple,3,0); //raum 4 tür links (oben)
    openDoors.emplace_back(0, doorTexture4, 48*multiple, 36*multiple,4,0); //raum 4 tür rechts (mittig)
    openDoors.emplace_back(0, doorTexture4, 45*multiple, 56*multiple,3,0); //raum 4 tür links (unten)
    openDoors.emplace_back(0, doorTexture4, 61*multiple, 51*multiple,1,0); //raum 4 tür oben (unten)
    openDoors.emplace_back(0, doorTexture4, 61*multiple, 47*multiple,2,0); //raum 5 tür unten
    openDoors.emplace_back(0, doorTexture4, 52*multiple, 36*multiple,3,0); //raum 5 tür links
    openDoors.emplace_back(0, doorTexture4, 35*multiple, 21*multiple,2,0);//bossraum unten

}
std::vector<Machine> Machine::machines;

Machine::Machine(float posX, float posY, float oposX, float oposY, Texture2D texture, int step)
        : machinePositionX(posX), machinePositionY(posY), machineTexture(texture), filled(false), pickedUp(false), orbPositionX(oposX), orbPositionY(oposY), currentStep(step), animationFinished(false), frameCounter(0)
{
    machineRec = {machinePositionX, machinePositionY, 34, 34};
}

void Machine::draw() { //kann mit door zusammengeführt werden
    if (filled) {
        std::cout << "Machine is filled!" << std::endl;
        frameCounter++;
        int framesPerStep = 11; // Anzahl Frames pro Animationsschritt

        if (frameCounter >= framesPerStep) {
            currentStep++;
            frameCounter = 0;
        }

        if(currentStep > 3){
            currentStep = 0;
        }

        switch (currentStep) {
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
    orbRec = {orbPositionX +8, orbPositionY, 16, 16};
    if (CheckCollisionRecs(orbRec, MainCharacter::playerRec))
    {
        pickedUp = true;
    }

    if(!pickedUp)
    {
        Rectangle orbSourceRec = {0, 0, 32, 32};
        DrawTextureRec(TextureManager::getTexture("Orb"),orbSourceRec, {orbPositionX, orbPositionY}, WHITE);
    }
}

void Machine::update()
{
    if(CheckCollisionRecs(machineRec, MainCharacter::playerRec) && IsKeyPressed(KEY_E) && pickedUp)
    {
        filled = true;
        pickedUp = false;
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