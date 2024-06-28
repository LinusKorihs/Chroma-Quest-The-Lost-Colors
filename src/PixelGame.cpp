#include "Camera.h"
#include "Configuration.h"
#include "DrawMap.h"
#include "Item.h"
#include "PixelGame.h"
#include "TextureManage.h"
#include "MainCharacter.h"
#include "UnloadResources.h"

GameState currentGameState;

std::shared_ptr<Projectile> PixelGame::projectile_p;
std::shared_ptr<Projectile> PixelGame::projectileEnemy_p;
std::shared_ptr<MiniBoss> PixelGame::miniBoss_p;
//std::shared_ptr<Enemy> PixelGame::enemy_p;
EnemyManager PixelGame::enemyManager;
Texture2D PixelGame::slimeEnemyTexture;
Texture2D PixelGame::BossRed;
Vector2 PixelGame::BossRedPosition = {32*35, 32*65 - 20};

std::vector<PressurePlate> pressurePlates;

bool PixelGame::isPlayerKnocked = false;
Rectangle MainCharacter::playerCharacterRectangle;
Rectangle MainCharacter::playerCharacterHitRectangle;

void PixelGame::gameInit()
{
    slimeEnemyTexture = TextureManager::getTexture("SlimeEnemy");
    BossRed = TextureManager::getTexture("BossRed");
    //MainCharacter::setEnemy(enemy_p);
    MainCharacter::setEnemyManager(&enemyManager);
    enemyManager.addEnemy({32*35+30, 32*65-140}, slimeEnemyTexture, SLIMERED);
    enemyManager.addEnemy({32*35-30, 32*65-140}, slimeEnemyTexture, ENEMYBLUE);

    projectile_p = std::make_shared<Projectile>();
    MainCharacter::setProjectile(projectile_p);

    Texture2D plateTexture = TextureManager::getTexture("PlateNormal");
    pressurePlates.emplace_back(32 * 35, 32 * 63, 32, plateTexture);

    TextureManage::loadAudio();
    MainCharacter::playerHealth = 100;

    projectile_p->load();
    MainCharacter::initPlayer(TextureManager::getTexture("MainCharacter"));

    tson::Tileson tileson; // tileson parse
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

    Stone::initializeStones(stoneTexture, stoneSourceRect);
}

void PixelGame::drawObjects() //unload sieht noch bisschen weird aus
{
    MainCharacter::playerCharacterRectangle = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                               TextureManager::getTexture("MainCharacter").width * 0.15f,
                                               TextureManager::getTexture("MainCharacter").height * 0.15f};
    MainCharacter::playerCharacterHitRectangle = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                                  TextureManager::getTexture("MainCharacter").width * 0.18f,
                                                  TextureManager::getTexture("MainCharacter").height * 0.18f};

    if (Stone::drawStone == 0)
    {
        for (Stone &stone : Stone::stoneObjects)
        {
            stone.draw();
            stone.drawHitboxes();
        }

        for (const PressurePlate& plate : pressurePlates) // Draw pressure plates
        {
            plate.draw();
            plate.drawHitboxes();
        }

        Stone::drawStone = 1;
    }
}

void PixelGame::gameLoop(tson::Map &Map)
{
    static bool isBossInitialized = false;
    if (!isBossInitialized) {
        miniBoss_p = std::make_shared<MiniBoss>(BossRedPosition, BossRed, BOSSRED);
        isBossInitialized = true;
    }
    //enemy_p = std::make_shared<Enemy>(Vector2{250, 280}, slimeEnemyTexture, 2, 5.0f, SLIMERED);

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
        stone.drawHitboxes();
    }

    for (PressurePlate& plate : pressurePlates) // Draw pressure plates
    {
        plate.update();
        plate.draw();
        plate.drawHitboxes();
    }

    drawObjects();
    MainCharacter::updatePlayer(TextureManager::getTexture("MainCharacter"), GetFrameTime());
    MainCharacter character;
    Texture texture = TextureManager::getTexture("MainCharacter");
    MainCharacter::drawMainCharacter(texture, character);
    MainCharacter::isPlayerDead = false;

    enemyManager.updateEnemies(GetFrameTime());
    enemyManager.drawEnemies();
    miniBoss_p->updateBoss(GetFrameTime());
    miniBoss_p->drawBoss();


    //enemy_p->updateBoss(GetFrameTime());
    //enemy_p->drawBoss(slimeEnemyTexture);

    //projectileEnemy_p->update(GetFrameTime(), 2);
    //projectileEnemy_p->draw();
    projectile_p->update(GetFrameTime(), projectile_p->getProjectileDestination());
    projectile_p->draw();

    MainCharacter::attack();


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
    playerCamera::camera.target = (Vector2) {MainCharacter::playerPosX, MainCharacter::playerPosY};

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
    projectile_p->unload(); //Projectile Textur
    //projectileEnemy_p->unload(); //Projectile Enemy Textur
}

void PixelGame::drawHud()
{
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();
    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText("Score", "Punkte"), MainCharacter::playerScore),
             1700, 140, 20, BLACK);
}


