#include "Configuration.h"
#include "MainCharacter.h"
#include "Projectile.h"
#include "Objects.h"
#include "PixelGame.h"
#include "Enemy.h"

int MainCharacter::playerHealth = 100;
//int MainCharacter::damagePerFrame = 2;
bool MainCharacter::isPlayerDead = false;
int MainCharacter::playerScore = 0;
int MainCharacter::playerMana = 5;
float MainCharacter::playerSpawnPositionX = 1120; //32*35 in new, 80 in old
float MainCharacter::playerSpawnPositionY = 2590; //32*65 in new, 368 in old
float MainCharacter::playerCharacterTextureScale = 0.425f;
float MainCharacter::playerCharacterHitBoxScale = 0.425f;
float MainCharacter::playerPosX = MainCharacter::playerSpawnPositionX;
float MainCharacter::playerPosY = MainCharacter::playerSpawnPositionY;
std::shared_ptr<Projectile> MainCharacter::projectile_p = std::make_shared<Projectile>();
EnemyManager* MainCharacter::enemyManager = nullptr;
int MainCharacter::currentFrame;
int MainCharacter::framesCounter;
int MainCharacter::framesSpeed;
Rectangle MainCharacter::frameRec;
std::shared_ptr<Enemy> MainCharacter::enemy_p;
std::shared_ptr<EnemyManager> MainCharacter::enemyManager_p = std::make_shared<EnemyManager>();
lastDirection MainCharacter::lastDir;
punchDir MainCharacter::punch = none;
bool MainCharacter::animationFinished = false;

void MainCharacter::setEnemy(const std::shared_ptr<Enemy>& enemy)
{
    enemy_p = enemy;
}

void MainCharacter::setEnemyManager(EnemyManager* manager)
{
    enemyManager = manager;
}

void MainCharacter::setProjectile(const std::shared_ptr<Projectile>& projectile)
{
    projectile_p = projectile;
}

void MainCharacter::initPlayer(Texture myTexture)
{
    frameRec = {32, 0.0f, 32, 32};
    framesCounter = 0;
    currentFrame = 0;
    framesSpeed = 8;
    lastDir = LASTRIGHT;
}

void MainCharacter::updateRec()
{
    float xPos = playerPosX + 5; // Adjusted X Position
    float yPos = playerPosY + 4; // Adjusted Y Position
    float width = 20; // Hitbox Width
    float height = 28; // Hitbox Height

    //Rec für kollision des chars
    playerRec = {
            xPos,
            yPos,
            width,
            height
    };
    //Rec zum hitten von enemies
    HitRec = {
            playerPosX,
            playerPosY,
            32,
            32
    };
}

void MainCharacter::updatePlayer(Texture myTexture, float deltaTime)
{
    framesCounter++;

    if(IsKeyDown(KEY_S) && punch == none)
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(lastDir != LASTDOWN)
            {
                currentFrame = 0;
            }
            currentFrame++;

            if (currentFrame > 3 || currentFrame < 0) currentFrame = 0;

            frameRec.x = (float) currentFrame * 32;
        }
    }
    else if(IsKeyDown(KEY_D) && punch == none)
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(lastDir != LASTRIGHT)
            {
                currentFrame = 4;
            }
            currentFrame++;

            if (currentFrame > 7 || currentFrame < 4) currentFrame = 4;

            frameRec.x = (float) currentFrame * 32;
        }
    }
    else if(IsKeyDown(KEY_W) && punch == none)
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(lastDir != LASTUP)
            {
                currentFrame = 8;
            }
            currentFrame++;

            if (currentFrame > 11 || currentFrame < 8) currentFrame = 8;

            frameRec.x = (float) currentFrame * 32;
        }
    }
    else if(IsKeyDown(KEY_A) && punch == none)
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(lastDir != LASTLEFT)
            {
                currentFrame = 12;
            }
            currentFrame++;

            if (currentFrame > 15 || currentFrame < 12)
            {
                currentFrame = 12;
            }

            frameRec.x = (float) currentFrame * 32;
        }
    }
    else if(punch == down)
    {
        animationFinished = false;
        if (!animationFinished)
        {
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > 19 || currentFrame < 16)
                {
                    currentFrame = 16;
                }
                if(currentFrame == 19)
                {
                    animationFinished = true;
                    punch = none;
                }
                frameRec.x = (float) currentFrame * 32;
            }
        }
    }
    else if(punch == right)
    {
        animationFinished = false;
        if(!animationFinished)
        {
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > 23 || currentFrame < 20)
                {
                    currentFrame = 20;
                }
                if(currentFrame == 23)
                {
                    animationFinished = true;
                    punch = none;
                }
                frameRec.x = (float) currentFrame * 32;
            }
        }
    }
    else if(punch == up)
    {
        animationFinished = false;
        if (!animationFinished)
        {
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > 27 || currentFrame < 24)
                {
                    currentFrame = 24;
                }
                if(currentFrame == 27)
                {
                    animationFinished = true;
                    punch = none;
                }
                frameRec.x = (float) currentFrame * 32;
            }
        }
    }
    else if(punch == left)
    {
        animationFinished = false;
        if(!animationFinished) {
            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > 31 || currentFrame < 28)
                {
                    currentFrame = 28;
                }
                if(currentFrame == 31)
                {
                    animationFinished = true;
                    punch = none;
                }
                frameRec.x = (float) currentFrame * 32;
            }
        }
    }

}

void MainCharacter::drawMainCharacter(Texture myTexture, MainCharacter& character)
{
    // Draw the player sprite
    DrawTextureRec(myTexture, character.frameRec, {character.playerPosX, character.playerPosY}, WHITE);

    /*DrawRectangleLines(
            playerRec.x,
            playerRec.y,
            playerRec.width,
            playerRec.height,
            PURPLE
    ); */
}

float calculateSquaredDistance(float x1, float y1, float x2, float y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

void MainCharacter::moveMainCharacter(int moveDirection, float deltaTime)
{
    float newPositionX = MainCharacter::playerPosX;
    float newPositionY = MainCharacter::playerPosY;

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            newPositionX += ConfigConst::playerMoveSpeed;
            lastDir = LASTRIGHT;
            break;
        case KEY_LEFT:
        case KEY_A:
            newPositionX -= ConfigConst::playerMoveSpeed;
            lastDir = LASTLEFT;
            break;
        case KEY_UP:
        case KEY_W:
            newPositionY -= ConfigConst::playerMoveSpeed;
            lastDir = LASTUP;
            break;
        case KEY_DOWN:
        case KEY_S:
            newPositionY += ConfigConst::playerMoveSpeed;
            lastDir = LASTDOWN;
            break;
        default:
            break;
    }

    Rectangle newRec = {newPositionX + 4, newPositionY, playerRec.width, playerRec.height};

    for (const Rectangle &doorRec : currentGameState.doorRectangles)
    {
        if (CheckCollisionRecs(newRec, doorRec))
        {
            return;
        }
    }

    for (const Rectangle &wallRec : currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }

    Stone* nearestStone = nullptr;
    float nearestDistanceSquared = std::numeric_limits<float>::max();

    for (Stone &stone : Stone::stoneObjects)
    {
        if (CheckCollisionRecs(newRec, stone.getRectangle()))
        {
            nearestStone = &stone;
            break;
        }
    }

    if (nearestStone)
    {
        nearestStone->moveOneTile(moveDirection, currentGameState.wallRectangles);
    }
    else
    {
        // If no stone is to be moved, update player position
        playerPosX = newPositionX;
        playerPosY = newPositionY;
    }

    // Update all stones
    for (Stone &stone : Stone::stoneObjects)
    {
        stone.update(deltaTime);
    }

    if (!projectile_p->getActive())
    {
        if (lastDir == LASTLEFT)
        {
            projectile_p->setProjectileDestination(2);
        }

        if (lastDir == LASTRIGHT)
        {
            projectile_p->setProjectileDestination(1);
        }

        if (lastDir == LASTUP)
        {
            projectile_p->setProjectileDestination(3);
        }

        if (lastDir == LASTDOWN)
        {
            projectile_p->setProjectileDestination(4);
        }
    }
}

void MainCharacter::playerDeath()
{
    if (MainCharacter::playerHealth <= 0)
    {
        MainCharacter::isPlayerDead = true;
        currentGameState.changeGameState(MenuState::MainMenu);
        MainCharacter::playerHealth = 100;
        MainCharacter::isPlayerDead = true;
        MainCharacter::setSpawnPosition();
    }
}

void MainCharacter::receiveDamage()
{
    /*if (CheckCollisionRecs(MainCharacter::playerRec, PixelGame::lavaTileRectangle))
    {
        MainCharacter::playerHealth -= MainCharacter::damagePerFrame;
        if (MainCharacter::playerHealth <= 0)
        {
            playerDeath();
        }
    }*/
}

void MainCharacter::attack()
{
    if (IsKeyPressed(KEY_ENTER) && playerMana > 0 && !projectile_p->getActive()) //Projectile wird aktiviert
    {
        Vector2 startPosition;
        playerMana -= 1;
        if (lastDir == LASTRIGHT)
        {
            startPosition = {playerPosX + 20, playerPosY + 10};
        }
        if (lastDir == LASTLEFT)
        {
            startPosition = {playerPosX - 1, playerPosY + 10};
        }
        if (lastDir == LASTUP)
        {
            startPosition = {playerPosX + 10, playerPosY - 5};
        }
        if (lastDir == LASTDOWN)
        {
            startPosition = {playerPosX + 10, playerPosY + 20};
        }
        projectile_p->init(startPosition, {300.0f, 300.0f});
    }

    if (projectile_p->getActive())
    {
        enemyManager->checkProjectileEnemyCollision(projectile_p, enemy_p);
    }
    enemyManager->deleteEnemy();

    if(IsKeyPressed(KEY_SPACE) && punch == none)
    {
        if (lastDir == LASTRIGHT)
        {
            punch = right;
        }
        if (lastDir == LASTLEFT)
        {
            punch = left;
        }
        if (lastDir == LASTUP)
        {
            punch = up;
        }
        if (lastDir == LASTDOWN)
        {
            punch = down;
        }
    }

    for (const auto &enemy: enemyManager->enemies)  //es gibt noch einen bug dass man 2 mal spammen kann in dem moment wo das projektil den enemy trifft
    {
        if (CheckCollisionRecs(MainCharacter::HitRec, enemy->getRec()) && IsKeyPressed(KEY_SPACE))
        {
            enemy->enemyGetsHit();
            //hier cooldown einfügen
        }
    }
}

void MainCharacter::setSpawnPosition()
{
    playerPosX = MainCharacter::playerSpawnPositionX;
    playerPosY = MainCharacter::playerSpawnPositionY;
}

Rectangle MainCharacter::getRectangle() const
{
    Rectangle rect;
    rect.x = HitRec.x + 4.5;
    rect.y = HitRec.y + 2;
    rect.width = HitRec.width - 10;
    rect.height = HitRec.height - 4.5;
    return rect;
}

void MainCharacter::setPosition(Vector2 pos)
{
    playerPosX = pos.x;
    playerPosY = pos.y;
}

Vector2 MainCharacter::getPosition()
{
    return {playerPosX, playerPosY};
}