#include "Objects.h"
#include "TextureManage.h"
#include "MainCharacter.h"

int Stone::drawStone = 0;

std::vector<Stone> Stone::stoneObjects;

Stone::Stone(float stoneX, float stoneY, float stoneSize, Texture2D& stoneTexture, Rectangle& sourceRectangle)
        : stonePositionX(stoneX), stonePositionY(stoneY), stoneSize(stoneSize), stoneTexture(stoneTexture), sourceRectangle(sourceRectangle), velocityX(0), velocityY(0)
{
}

void Stone::draw() const
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

void Stone::move(int moveDirection, const std::vector<Rectangle>& wallRectangles)
{
    float speed = 2.0f; // Adjust speed as necessary

    switch (moveDirection)
    {
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
        default:
            break;
    }

    float newX = stonePositionX + velocityX;
    float newY = stonePositionY + velocityY;

    if (!checkCollisionWithWalls(newX, newY, wallRectangles) && !checkCollisionWithStones(newX, newY))
    {
        stonePositionX = newX;
        stonePositionY = newY;
    }
    else
    {
        velocityX = 0; // Stop the stone if there's a collision
        velocityY = 0;
    }
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
    Stone::stoneObjects.emplace_back(multiple * 32, multiple * 61, multiple, stoneTexture, stoneSourceRect);
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
    Stone::stoneObjects.emplace_back(multiple * 38, multiple * 63, multiple, stoneTexture, stoneSourceRect);

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
    drawHitboxes();
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


Door::Door(int doorOp, Texture2D texture, float positionX, float positionY, int doorNum)
        : doorOpen(doorOp), doorTexture(texture), doorPositionX(positionX), doorPositionY(positionY), doorNumber(doorNum)
{
}

void Door::draw() const
{
    DrawTextureV(doorTexture, {doorPositionX, doorPositionY}, WHITE);
    //DrawRectangleLines(Door::getRectangle().x,Door::getRectangle().y,Door::getRectangle().width,Door::getRectangle().height, RED);
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
    openDoors.emplace_back(1, doorTexture1, 1120, 1888,1); //raum 1 tür oben
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
    openDoors.emplace_back(0, doorTexture1, 1120, 672,1); //bossraum

}