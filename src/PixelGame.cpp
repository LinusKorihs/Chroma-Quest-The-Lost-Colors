#include "Camera.h"
#include "Configuration.h"
#include "DrawMap.h"
#include "Item.h"
#include "PixelGame.h"
#include "LoadResources.h"
#include "MainCharacter.h"
#include "UnloadResources.h"

GameState currentGameState;

std::shared_ptr<Enemy> PixelGame::enemyPointer;
std::shared_ptr<Projectile> PixelGame::projectileEnemyPointer;

Texture2D PixelGame::lavaTileTexture;
Texture2D PixelGame::slimeEnemyTexture;
Texture2D PixelGame::gameTilesetTexture;

Enemy PixelGame::enemy;

bool PixelGame::isPlayerKnocked = false;

Rectangle MainCharacter::playerCharacterRectangle;
Rectangle MainCharacter::playerCharacterHitRectangle;
Rectangle PixelGame::lavaTileRectangle;

void PixelGame::gameInit()
{
    Projectile::projectilePointer = std::make_shared<Projectile>();
    projectileEnemyPointer = std::make_shared<Projectile>();

    LoadResources::loadAudio();
    LoadResources::loadTextures();

    Projectile::projectilePointer->load();
    projectileEnemyPointer->load();

    MainCharacter::playerHealth = 100;

    loadTexture(lavaTileTexture, "assets/graphics/Tiles/Lava.png");
    loadTexture(Item::meatItemTexture, "assets/graphics/Items/Fleisch.png");
    loadTexture(Item::fruitItemTexture, "assets/graphics/Items/Frucht.png");
    loadTexture(slimeEnemyTexture, "assets/graphics/Enemys/TestSlime.png");

    tson::Tileson tileson;    // tileson parse
    auto MapPtr = tileson.parse("assets/graphics/Old TileSet & TileMap/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK)
    {
        std::cout
                << LanguageManager::getLocalizedGameText("Failed to parse map, error: ",
                                                         "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }

    playerCamera();

    Rectangle stoneSourceRect = {144,96,16,16};
    int x = 16 * 6;
    int y = 20 * 16;

    Stone::stoneObjects.push_back(Stone(x, y, 32, gameTilesetTexture, stoneSourceRect));
}

void PixelGame::drawObjects() //unload sieht noch bisschen weird aus
{
    MainCharacter::playerCharacterRectangle = {MainCharacter::playerPositionX, MainCharacter::playerPositionY, ConfigConst::playerMC.width * 0.15f, ConfigConst::playerMC.height * 0.15f};
    MainCharacter::playerCharacterHitRectangle = {MainCharacter::playerPositionX, MainCharacter::playerPositionY, ConfigConst::playerMC.width * 0.18f, ConfigConst::playerMC.height * 0.18f};
    lavaTileRectangle = {300.0f, 275.0f, lavaTileTexture.width / 25.0f, lavaTileTexture.height / 25.0f};
    Item::meatItemRectangle = {450.0f, 275.0f, Item::meatItemTexture.width / 1.5f, Item::meatItemTexture.height / 1.5f};
    Item::fruitItemRectangle = {150.0f, 100.0f, Item::fruitItemTexture.width / 1.5f, Item::fruitItemTexture.height / 1.5f};

    if(!ConfigNotConst::shouldUnloadMeat)
    {
        drawTexture(Item::meatItemTexture, {450.0f, 275.0f, Item::meatItemTexture.width / 1.5f, Item::meatItemTexture.height / 1.5f});
    }
    if(!ConfigNotConst::shouldUnloadFruit)
    {
        drawTexture(Item::fruitItemTexture, {150.0f, 100.0f, Item::fruitItemTexture.width / 1.5f, Item::fruitItemTexture.height / 1.5f});
    }

    drawTexture(lavaTileTexture, {300.0f, 275.0f, lavaTileTexture.width / 25.0f, lavaTileTexture.height / 25.0f});

    if (CheckCollisionRecs(MainCharacter::playerCharacterRectangle, Item::fruitItemRectangle))
    {
        if(!ConfigNotConst::shouldUnloadFruit)
        {
            ConfigNotConst::shouldUnloadFruit = true;
            MainCharacter::playerHealth += 25;
            if (MainCharacter::playerHealth >= 100)
            {
                MainCharacter::playerHealth = 100;
            }

            UnloadTexture(Item::fruitItemTexture);
            MainCharacter::playerScore += 50;
        }
    }

    if (CheckCollisionRecs(MainCharacter::playerCharacterRectangle, Item::meatItemRectangle))
    {
        if(!ConfigNotConst::shouldUnloadMeat)
        {
            ConfigNotConst::shouldUnloadMeat = true;
            MainCharacter::playerHealth += 50;
            MainCharacter::playerMana += 1;
            if(MainCharacter::playerMana >= 5)
            {
                MainCharacter::playerMana = 5;
            }
            if (MainCharacter::playerHealth >= 100)
            {
                MainCharacter::playerHealth = 100;
            }

            UnloadTexture(Item::meatItemTexture);
            MainCharacter::playerScore += 100;
        }
    }
}

void PixelGame::gameLoop(tson::Map &Map)
{
    enemyPointer = std::make_shared<Enemy>(Vector2{250, 280}, slimeEnemyTexture, 2, 5.0f, SLIMERED);

    while (!WindowShouldClose() && ConfigNotConst::isGameRunning)
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            ConfigNotConst::isGamePaused = true;
        }

        if (ConfigNotConst::isGamePaused)
        {
            currentGameState.changeGameState(MenuState::PauseMenu);
            currentGameState.currentGameMenu = MenuState::PauseMenu;
            Menu::drawPauseMenu(currentGameState);
        }

        if (currentGameState.currentGameMenu == MenuState::MainMenu || !ConfigNotConst::isGameRunning)
        {
            break;
        }

        BeginDrawing();
        BeginMode2D(playerCamera::camera);
        ClearBackground(DARKGRAY);

        DrawMap::drawTiles(Map, ConfigConst::tileSet);

        for (const Stone& stone : Stone::stoneObjects)
        {
            stone.draw();
        }

        drawObjects();
        MainCharacter::drawMainCharacter(ConfigConst::playerMC);
        MainCharacter::isPlayerDead = false;

        enemyPointer->updateEnemy(GetFrameTime(), slimeEnemyTexture);
        enemyPointer->drawEnemy(slimeEnemyTexture);

        MainCharacter::attack();
        Enemy::enemyAttack();

        Projectile::projectilePointer->update(GetFrameTime());  // Update and draw the player projectile
        Projectile::projectilePointer->draw();

        projectileEnemyPointer->update(GetFrameTime()); // Update and draw the enemy projectile
        projectileEnemyPointer->draw();

        if (IsKeyPressed(KEY_ESCAPE))
        {
            UnloadResources::unloadAudio();
            UnloadResources::unloadTexture();

            currentGameState.changeGameState(MenuState::PauseMenu);
            return;
        }

        bool isMoving = false; //movement sollte noch separiert werden

        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::UP]))
        {
            MainCharacter::moveMainCharacter(KEY_UP, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::DOWN]))
        {
            MainCharacter::moveMainCharacter(KEY_DOWN, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::LEFT]))
        {
            MainCharacter::moveMainCharacter(KEY_LEFT, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::RIGHT]))
        {
            MainCharacter::moveMainCharacter(KEY_RIGHT, GetFrameTime());
            isMoving = true;
        }
        if (isMoving && !IsSoundPlaying(ConfigNotConst::playerWalkingSound))
        {
            PlaySound(ConfigNotConst::playerWalkingSound);
        }
        else if (!isMoving && IsSoundPlaying(ConfigNotConst::playerWalkingSound))
        {
            StopSound(ConfigNotConst::playerWalkingSound);
        }
        UpdateMusicStream(ConfigNotConst::gameBackgroundMusic);
        playerCamera::camera.target = (Vector2){MainCharacter::playerPositionX, MainCharacter::playerPositionY };

        if (CheckCollisionRecs(MainCharacter::playerCharacterRectangle, lavaTileRectangle)) //muss noch separiert werden
        {
            MainCharacter::playerHealth -= MainCharacter::damagePerFrame;
            if (MainCharacter::playerHealth <= 0)
            {
                MainCharacter::playerHealth = 0;
                unloadAll();
                currentGameState.changeGameState(MenuState::MainMenu);
                MainCharacter::playerHealth = 100;
                MainCharacter::isPlayerDead = true;
                MainCharacter::setSpawnPosition();
                return;
            }
        }

        if (WindowShouldClose())
        {
            CloseWindow();
            unloadAll();
            exit(0);
        }
        EndMode2D();
        drawHud();
        EndDrawing();
    }

    CloseWindow();
    unloadAll();
}

void PixelGame::loadTexture(Texture2D &loadTexture, const char* textureFilePath)
{
    loadTexture = LoadTexture(textureFilePath);
}

void PixelGame::drawTexture(Texture2D &texture, Rectangle destination)
{
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(texture, source, destination, origin, 0.0f, WHITE);
}

void PixelGame::unloadTexture(Texture2D &unloadTexture)
{
    UnloadTexture(unloadTexture);
}

void PixelGame::unloadAll()
{
    UnloadResources::unloadAudio();
    UnloadResources::unloadTexture();
    unloadTexture(lavaTileTexture);
    unloadTexture(Item::meatItemTexture);
    unloadTexture(Item::fruitItemTexture);
    Projectile::projectilePointer->unload(); //Projectiles Textur
    projectileEnemyPointer->unload(); //Projectiles Enemy Textur
    unloadTexture(slimeEnemyTexture);
    unloadTexture(gameTilesetTexture);
}

void PixelGame::drawHud()
{
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();
    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText("Score", "Punkte"), MainCharacter::playerScore), 1700, 140, 20, BLACK);
}


