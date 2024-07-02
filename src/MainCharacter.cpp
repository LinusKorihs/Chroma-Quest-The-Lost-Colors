#include "Configuration.h"
#include "TextureManage.h"
#include "MainCharacter.h"
#include "Projectile.h"
#include "Objects.h"
#include "PixelGame.h"
#include "Enemy.h"


int MainCharacter::playerHealth = 100;
int MainCharacter::damagePerFrame = 2;
bool MainCharacter::isPlayerDead = false;
int MainCharacter::playerScore = 0;
int MainCharacter::playerMana = 5;
float MainCharacter::playerSpawnPositionX = 32*35; //32*35 in new, 80 in old
float MainCharacter::playerSpawnPositionY = 32*65; //32*65 in new, 368 in old
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
    frameRec = {32, 0.0f, (float)myTexture.width/32, (float)myTexture.height};
    framesCounter = 0;
    currentFrame = 0;
    framesSpeed = 8;
}

void MainCharacter::updatePlayer(Texture myTexture, float deltaTime)
{
    framesCounter++;

    if(IsKeyDown(KEY_S))
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(!ConfigNotConst::lastDirectionDown)
            {
                currentFrame = 0;
            }
            currentFrame++;

            if (currentFrame > 3 || currentFrame < 0) currentFrame = 0;

            frameRec.x = (float) currentFrame * (float) myTexture.width / 32;
        }
    }
    else if(IsKeyDown(KEY_D))
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(!ConfigNotConst::lastDirectionRight)
            {
                currentFrame = 4;
            }
            currentFrame++;

            if (currentFrame > 7 || currentFrame < 4) currentFrame = 4;

            frameRec.x = (float) currentFrame * (float) myTexture.width / 32;
        }
    }
    else if(IsKeyDown(KEY_W))
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(!ConfigNotConst::lastDirectionUp)
            {
                currentFrame = 8;
            }
            currentFrame++;

            if (currentFrame > 11 || currentFrame < 8) currentFrame = 8;

            frameRec.x = (float) currentFrame * (float) myTexture.width / 32;
        }
    }
    else if(IsKeyDown(KEY_A))
    {
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            if(!ConfigNotConst::lastDirectionLeft)
            {
                currentFrame = 12;
            }
            currentFrame++;

            if (currentFrame > 15 || currentFrame < 12)
            {
                currentFrame = 12;
            }

            frameRec.x = (float) currentFrame * (float) myTexture.width / 32;
        }
    }

    playerCharacterRectangle = {
            playerPosX,
            playerPosY,
            myTexture.width * playerCharacterTextureScale,
            myTexture.height * playerCharacterTextureScale
    };

    playerCharacterHitRectangle = {
            playerPosX + (myTexture.width * (playerCharacterTextureScale - playerCharacterHitBoxScale)) / 2.0f,
            playerPosY + (myTexture.height * (playerCharacterTextureScale - playerCharacterHitBoxScale)) / 2.0f,
            myTexture.width * playerCharacterHitBoxScale,
            myTexture.height * playerCharacterHitBoxScale
    };
}

void MainCharacter::drawMainCharacter(Texture myTexture, MainCharacter& character)
{
    // Draw the player sprite
    DrawTextureRec(myTexture, character.frameRec, {character.playerPosX, character.playerPosY}, WHITE);

    DrawRectangleLines(
            playerCharacterHitRectangle.x,
            playerCharacterHitRectangle.y,
            playerCharacterHitRectangle.width,
            playerCharacterHitRectangle.height,
            GREEN
    );
}

float calculateSquaredDistance(float x1, float y1, float x2, float y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

void MainCharacter::moveMainCharacter(int moveDirection, float deltaTime) {

        float newPositionX = MainCharacter::playerPosX;
        float newPositionY = MainCharacter::playerPosY;

        switch (moveDirection) {
            case KEY_RIGHT:
            case KEY_D:
                newPositionX += ConfigConst::playerMoveSpeed;
                ConfigNotConst::lastDirectionLeft = false;
                ConfigNotConst::lastDirectionUp = false;
                ConfigNotConst::lastDirectionDown = false;
                ConfigNotConst::lastDirectionRight = true;
                break;
            case KEY_LEFT:
            case KEY_A:
                newPositionX -= ConfigConst::playerMoveSpeed;
                ConfigNotConst::lastDirectionLeft = true;
                ConfigNotConst::lastDirectionUp = false;
                ConfigNotConst::lastDirectionDown = false;
                ConfigNotConst::lastDirectionRight = false;
                break;
            case KEY_UP:
            case KEY_W:
                newPositionY -= ConfigConst::playerMoveSpeed;
                ConfigNotConst::lastDirectionUp = true;
                ConfigNotConst::lastDirectionDown = false;
                ConfigNotConst::lastDirectionRight = false;
                ConfigNotConst::lastDirectionLeft = false;
                break;
            case KEY_DOWN:
            case KEY_S:
                newPositionY += ConfigConst::playerMoveSpeed;
                ConfigNotConst::lastDirectionUp = false;
                ConfigNotConst::lastDirectionDown = true;
                ConfigNotConst::lastDirectionRight = false;
                ConfigNotConst::lastDirectionLeft = false;
                break;
            default:
                break;
        }
        Stone *nearestStone = nullptr;
        float nearestDistanceSquared = std::numeric_limits<float>::max();
        //Rectangle newRec = {newPositionX, newPositionY, static_cast<float>(TextureManager::getTexture("MainCharacter").width / 32) /* * playerCharacterHitBoxScale*/, static_cast<float>(TextureManager::m_textures["MainCharacter"].height) /* * playerCharacterHitBoxScale */};
        Rectangle newRec = {newPositionX, newPositionY, 30, 30};
        for (const Rectangle &wallRec: currentGameState.wallRectangles) {
            if (CheckCollisionRecs(newRec, wallRec)) {
                return;
            }
        }

        for (Stone &stone: Stone::stoneObjects) {
            float stoneCenterX = stone.getRectangle().x + stone.getRectangle().width / 2.0f;
            float stoneCenterY = stone.getRectangle().y + stone.getRectangle().height / 2.0f;
            /*float playerCenterX = newPositionX + (TextureManager::getTexture("MainCharacter").width / 32 * playerCharacterHitBoxScale) / 2.0f;
            float playerCenterY = newPositionY + (TextureManager::getTexture("MainCharacter").height  * playerCharacterHitBoxScale) / 2.0f;*/
            float playerCenterX = newPositionX + 30 / 2.0f;
            float playerCenterY = newPositionY + 30 / 2.0f;

            float distanceSquared = calculateSquaredDistance(playerCenterX, playerCenterY, stoneCenterX, stoneCenterY);

            if (distanceSquared < nearestDistanceSquared) {
                nearestDistanceSquared = distanceSquared;
                nearestStone = &stone;
            }
        }

        // Attempt to move the nearest stone if one was found within a reasonable distance
        if (nearestStone && nearestDistanceSquared < 1000.0f) // Adjust threshold as needed
        {
            nearestStone->move(moveDirection, currentGameState.wallRectangles);
        } else {
            // If no stone is close enough, update player position
            playerPosX = newPositionX;
            playerPosY = newPositionY;
        }

        if (!projectile_p->getActive()) //Richtung der Projektile basierend auf Player movement (wird in Projectiles.h übergeben)
        {
            if (ConfigNotConst::lastDirectionLeft) //sollte enum werden
            {
                projectile_p->setProjectileDestination(2);
            }
            if (ConfigNotConst::lastDirectionRight) {
                projectile_p->setProjectileDestination(1);
            }
            if (ConfigNotConst::lastDirectionUp) {
                projectile_p->setProjectileDestination(3);
            }
            if (ConfigNotConst::lastDirectionDown) {
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
    /*if (CheckCollisionRecs(MainCharacter::playerCharacterRectangle, PixelGame::lavaTileRectangle))
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
        if (ConfigNotConst::lastDirectionRight)
        {
            startPosition = {playerPosX + 20, playerPosY + 10};
        }
        if (ConfigNotConst::lastDirectionLeft)
        {
            startPosition = {playerPosX - 1, playerPosY + 10};
        }
        if (ConfigNotConst::lastDirectionUp)
        {
            startPosition = {playerPosX + 10, playerPosY - 5};
        }
        if (ConfigNotConst::lastDirectionDown)
        {
            startPosition = {playerPosX + 10, playerPosY + 20};
        }

        projectile_p->init(startPosition, {300.0f, 300.0f});

    }

    if(projectile_p->getActive())
    {
        enemyManager->checkProjectileEnemyCollision(projectile_p, enemy_p);
    }
    enemyManager->deleteEnemy();

   /*
    for(const auto &enemy : enemyManager->enemies)
    {
        if (CheckCollisionRecs(MainCharacter::playerCharacterHitRectangle, enemy->getBossRec()) && !enemy->getBossDeath())
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                enemy->bossGetsHit();
            }
        }
    }*/
}

void MainCharacter::setSpawnPosition()
{
    playerPosX = MainCharacter::playerSpawnPositionX;
    playerPosY = MainCharacter::playerSpawnPositionY;
}

Rectangle MainCharacter::getRectangle() const
{
    Rectangle rect;
    rect.x = this->playerCharacterHitRectangle.x;
    rect.y = this->playerCharacterHitRectangle.y;
    rect.width = this->playerCharacterHitRectangle.width;
    rect.height = this->playerCharacterHitRectangle.height;
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