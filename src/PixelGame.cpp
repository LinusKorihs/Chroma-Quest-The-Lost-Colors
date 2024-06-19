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

Texture2D PixelGame::slimeEnemyTexture;

Enemy PixelGame::enemy;

bool PixelGame::isPlayerKnocked = false;

Rectangle MainCharacter::playerCharacterRectangle;
Rectangle MainCharacter::playerCharacterHitRectangle;

void PixelGame::gameInit()
{
    Projectile::projectilePointer = std::make_shared<Projectile>();
    projectileEnemyPointer = std::make_shared<Projectile>();

    LoadResources::loadAudio();

    Projectile::projectilePointer->load();
    projectileEnemyPointer->load();

    MainCharacter::playerHealth = 100;

    tson::Tileson tileson;    // tileson parse
    auto MapPtr = tileson.parse("assets/graphics/TileSet & TileMap/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK)
    {
        std::cout
                << LanguageManager::getLocalizedGameText("Failed to parse map, error: ",
                                                         "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }

    playerCamera();

    Texture2D stoneTexture = TextureManager::getTexture("Stone");
    Rectangle stoneSourceRect = {0, 0, (float)stoneTexture.width, (float)stoneTexture.height};

    if (!IsTextureReady(stoneTexture))
    {
        std::cerr << "Error: Stone texture not loaded" << std::endl;
        return;
    }

    Stone::stoneObjects.emplace_back(32*32,32*61, 32, stoneTexture, stoneSourceRect); // Create instances of Stone using StoneData
    Stone::stoneObjects.emplace_back(32*32,32*62, 32, stoneTexture, stoneSourceRect);
    Stone::stoneObjects.emplace_back(32*32,32*63, 32, stoneTexture, stoneSourceRect);
}

void PixelGame::drawObjects() //unload sieht noch bisschen weird aus
{
    MainCharacter::playerCharacterRectangle = {MainCharacter::playerPositionX, MainCharacter::playerPositionY,
                                               TextureManager::getTexture("MainCharacter").width * 0.15f,
                                               TextureManager::getTexture("MainCharacter").height * 0.15f};
    MainCharacter::playerCharacterHitRectangle = {MainCharacter::playerPositionX, MainCharacter::playerPositionY,
                                                  TextureManager::getTexture("MainCharacter").width * 0.18f,
                                                  TextureManager::getTexture("MainCharacter").height * 0.18f};

    if (Stone::drawStone == 0)
    {
        for (Stone &stone: Stone::stoneObjects)
        {
            stone.draw();
        }
    }
    Stone::drawStone = 1;
}

void PixelGame::gameLoop(tson::Map &Map)
{
    enemyPointer = std::make_shared<Enemy>(Vector2{250, 280}, slimeEnemyTexture, 2, 5.0f, SLIMERED);

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

    BeginMode2D(playerCamera::camera); //BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawMap::drawTiles(Map, TextureManager::m_textures["TileSet"]);

    for (const Stone &stone: Stone::stoneObjects)
    {
        stone.draw();
    }

    drawObjects();
    MainCharacter::drawMainCharacter(TextureManager::getTexture("MainCharacter"));

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
    playerCamera::camera.target = (Vector2) {MainCharacter::playerPositionX, MainCharacter::playerPositionY};

    if (WindowShouldClose())
    {
        CloseWindow();
        unloadAll();
        exit(0);
    }
    EndMode2D();
    drawHud();
    //EndDrawing();
}

void PixelGame::unloadAll()
{
    UnloadResources::unloadAudio();
    Projectile::projectilePointer->unload(); //Projectiles Textur
    projectileEnemyPointer->unload(); //Projectiles Enemy Textur
}

void PixelGame::drawHud()
{
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();
    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText("Score", "Punkte"), MainCharacter::playerScore),
             1700, 140, 20, BLACK);
}


