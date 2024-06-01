#include "PixelGame.h"
#include "Audio.h"
#include "Menu.h"
#include "InGameHud.h"
#include "ApplicationState.h"

ApplicationState gameState;

//definition of static variables
std::vector<Stone> PixelGame::stones;

Texture2D PixelGame::lavaTexture;
Texture2D PixelGame::meatTexture;
Texture2D PixelGame::fruitTexture;
Texture2D PixelGame::projectileTexture;
Texture2D PixelGame::slimeTexture;
Texture2D PixelGame::tilesetTexture;

Camera2D PixelGame::camera;

float PixelGame::mcX = 80;
float PixelGame::mcY = 368;

Rectangle PixelGame::characterRec;
Rectangle PixelGame::lavaRec;
Rectangle PixelGame::meatRec;
Rectangle PixelGame::fruitRec;
Rectangle PixelGame::projectileRec;

struct Projectile PixelGame::projectile;
struct Enemy PixelGame::enemy;

void PixelGame::DrawTiles(tson::Map &Map, Texture2D &myTexture)
{
    auto layer1 = Map.getLayer("Kachelebene 2")->getData();
    DrawLayer(layer1, Map, myTexture);

    auto layer2 = Map.getLayer("animation")->getData();
    DrawLayer(layer2, Map, myTexture);
}

void PixelGame::DrawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture)
{
    const int currentFrame = int(GetTime() * 6) % 4;

    float tileWidth = 16;
    int tileSetColumns = 16;

    for (int y = 0; y < Map.getSize().y; y++)
    {
        for (int x = 0; x < Map.getSize().x; x++)
        {
            int data = layer[y * Map.getSize().x + x];

            // Get the tile from the tileset
            tson::Tileset* tileset = Map.getTilesetByGid(data);
            if (tileset != nullptr)
            {
                tson::Tile* tile = tileset->getTile(data);

                // Check if the tile is a wall
                if (tile != nullptr && tile->get<bool>("Wall"))
                {
                    // Create a Rectangle for the tile and add it to the list of wall rectangles
                    Rectangle wallRec = {(float) x * tileWidth * 2, (float) y * tileWidth * 2, tileWidth * 2, tileWidth * 2};
                    gameState.wallRecs.push_back(wallRec);
                }
            }

            data--;
            if (data < 0) continue;

            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle dest = {(float) x * tileWidth * 2, (float) y * tileWidth * 2, tileWidth * 2, tileWidth * 2};

            //animation layer
            if (data >= 0xE0)
            {
                source.x += (float) (currentFrame * tileWidth);
            }

            DrawTexturePro(myTexture, source, dest, {0, 0}, 0, WHITE);

        }
    }
}

void PixelGame::DrawSprite(Texture2D &myTexture)
{
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle dest = {mcX, mcY, myTexture.width * 0.15f, myTexture.height * 0.15f};

    DrawTexturePro(myTexture, source, dest, {0, 0}, 0.0f, WHITE);
}

void PixelGame::MoveCharacter(int direction)
{
    float newPositionX = mcX;
    float newPositionY = mcY;

    switch (direction)
    {
        case KEY_RIGHT:
        case KEY_D:
            newPositionX += gameState.moveSpeed;
            break;
        case KEY_LEFT:
        case KEY_A:
            newPositionX -= gameState.moveSpeed;
            break;
        case KEY_UP:
        case KEY_W:
            newPositionY -= gameState.moveSpeed;
            break;
        case KEY_DOWN:
        case KEY_S:
            newPositionY += gameState.moveSpeed;
            break;
    }

    Rectangle newRec = {newPositionX, newPositionY, gameState.myMC.width * 0.15f, gameState.myMC.height * 0.15f};

    for (const Rectangle& wallRec : gameState.wallRecs)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }
    bool stoneCollision = false;
    for(Stone& stone : stones)
    {
        if(CheckCollisionRecs(newRec, stone.getRectangle()))
        {
            stone.move(direction,gameState.wallRecs);
            stoneCollision = true;
        }
    }
    if(!stoneCollision) {
        mcX = newPositionX;
        mcY = newPositionY;
    }

}

void PixelGame::GameInit()
{
    Audio::loadResourcesAndInitAudio();
    LoadTextureX(lavaTexture, "assets/graphics/backgrounds/Lava.png");
    LoadTextureX(meatTexture, "assets/graphics/Fleisch.png");
    LoadTextureX(fruitTexture, "assets/graphics/Frucht.png");
    LoadTextureX(projectileTexture, "assets/graphics/necrobolt1_strip.png");
    LoadTextureX(slimeTexture, "assets/graphics/slime-Sheet.png");
    LoadTextureX(tilesetTexture, "assets/graphics/testimage.png");

    gameState.health = 100;

    // tileson parse
    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK) {
        std::cout
                << gameState.getLocalizedText("Failed to parse map, error: ", "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }
    //camera init
    camera = { 0 };
    camera.target = (Vector2){ 80,368 };
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    Rectangle stoneSourceRect = {144,96,16,16};
    int x = 16*6;
    int y = 20*16;

    stones.push_back(Stone(x,y,32,tilesetTexture,stoneSourceRect));


}

void PixelGame::InitProjectile(Projectile &proj, Vector2 startPosition, Vector2 speed) {
    proj.position = startPosition;
    proj.speed = speed;
    proj.isActive = true;
}

void PixelGame::UpdateProjectile(Projectile &proj, float deltaTime) {
    projectileRec = {proj.position.x, proj.position.y, projectileTexture.width / 4.0f, static_cast<float>(projectileTexture.height)};

    if (proj.isActive) {
        proj.position.x += proj.speed.x * deltaTime;
        proj.position.y += proj.speed.y * deltaTime;
        for (const Rectangle& wallRec : gameState.wallRecs)
        {
            if (CheckCollisionRecs(projectileRec, wallRec) or proj.position.x > mcX + 200)
            {
                proj.isActive = false;
            }
        }
    }
}

void PixelGame::DrawProjectile(const Projectile &proj) {
    if (proj.isActive) {
        DrawTextureEx(projectileTexture, proj.position, 0, 1.0f, WHITE);
    }
}

void PixelGame::Attack() {
    if (IsKeyPressed(KEY_ENTER) && gameState.mana > 0 && !projectile.isActive) {
        gameState.mana -= 1;
        InitProjectile(projectile, {mcX, mcY}, {200.0f, 0.0f});
    }
}


void PixelGame::DrawObjects() //unload sieht noch bisschen weird aus
{

    characterRec = {mcX, mcY, gameState.myMC.width * 0.15f, gameState.myMC.height * 0.15f};
    lavaRec = {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f};
    meatRec = {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f};
    fruitRec = {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f};

    if(!gameState.meatUnload) {
        DrawTexture(meatTexture, {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f});
    }
    if(!gameState.fruitUnload) {
        DrawTexture(fruitTexture, {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f});
    }
    DrawTexture(lavaTexture, {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f});


    if (CheckCollisionRecs(characterRec, fruitRec))
    {
        if(!gameState.fruitUnload) {
            gameState.fruitUnload = true;
            gameState.health += 25;
            if (gameState.health >= 100) {
                gameState.health = 100;
            }

            UnloadTexture(fruitTexture);
            gameState.score += 50;
        }
    }

    if (CheckCollisionRecs(characterRec, meatRec))
    {
        if(!gameState.meatUnload) {
            gameState.meatUnload = true;
            gameState.health += 50;
            gameState.mana += 1;
            if(gameState.mana >= 5) {
                gameState.mana = 5;
            }
            if (gameState.health >= 100) {
                gameState.health = 100;
            }

            UnloadTexture(meatTexture);
            gameState.score += 100;
        }
    }
}

void PixelGame::GameLoop(tson::Map &Map)
{
    EnemyInit(enemy, {250.0f, 280.0f}, slimeTexture);

    while (!WindowShouldClose() && gameState.gameIsRunning)
    {

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState.isPaused = true;
        }

        if (gameState.isPaused)
        {
            gameState.changeState(MenuState::PauseMenu);
            gameState.currentMenu = MenuState::PauseMenu;
            Menu::drawPauseMenu(gameState);
        }

        if (gameState.currentMenu == MenuState::MainMenu || !gameState.gameIsRunning)
        {
            break;
        }

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(DARKGRAY);

        DrawTiles(Map, gameState.myTexture);

        for (const Stone& stone : stones)
        {
            stone.draw();
        }

        DrawObjects();

        DrawSprite(gameState.myMC);
        gameState.playerDeath = 0;

        EnemyUpdate(enemy, GetFrameTime(), slimeTexture);
        DrawEnemies(enemy, slimeTexture);

        Attack();
        UpdateProjectile(projectile, GetFrameTime());
        DrawProjectile(projectile);


        if (IsKeyPressed(KEY_ESCAPE)) {
            Audio::unloadResourcesAndCloseAudio();
            gameState.changeState(MenuState::PauseMenu);
            return;
        }

        bool isMoving = false; //movement sollte noch separiert werden

        if (IsKeyDown(gameState.keyBindings[UP])) {
            MoveCharacter(KEY_UP);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[DOWN])) {
            MoveCharacter(KEY_DOWN);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[LEFT])) {
            MoveCharacter(KEY_LEFT);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[RIGHT])) {
            MoveCharacter(KEY_RIGHT);
            isMoving = true;
        }
        if (isMoving && !IsSoundPlaying(gameState.walkingSound)) {
            PlaySound(gameState.walkingSound);
        } else if (!isMoving && IsSoundPlaying(gameState.walkingSound)) {
            StopSound(gameState.walkingSound);
        }
        UpdateMusicStream(gameState.backgroundMusic);
        camera.target = (Vector2){ mcX,mcY };

        if (CheckCollisionRecs(characterRec, lavaRec)) //muss noch separiert werden
        {
            gameState.health -= gameState.damage_per_frame;
            if (gameState.health <= 0) {
                gameState.health = 0;
                UnloadAll();
                gameState.changeState(MenuState::MainMenu);
                gameState.health = 100;
                gameState.playerDeath = 1;
                return;
            }
        }

        if (WindowShouldClose())
        {
            CloseWindow();
            UnloadAll();
            exit(0);
        }
        EndMode2D();
        DrawHud();
        EndDrawing();
    }

    CloseWindow();
    UnloadAll();
}

void PixelGame::LoadTextureX(Texture2D &texture, const char* path)
{
    texture = LoadTexture(path);
}

void PixelGame::DrawTexture(Texture2D &texture, Rectangle dest)
{
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void PixelGame::UnloadTextureX(Texture2D &texture)
{
    UnloadTexture(texture);
}

void PixelGame::UnloadAll()
{
    Audio::unloadResourcesAndCloseAudio();
    UnloadTextureX(lavaTexture);
    UnloadTextureX(meatTexture);
    UnloadTextureX(fruitTexture);
    UnloadTextureX(projectileTexture);
    UnloadTextureX(slimeTexture);
    UnloadTextureX(tilesetTexture);
}

void PixelGame::DrawHud()
{
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();
    DrawText(TextFormat("%s: %i", gameState.getLocalizedText("Score", "Punkte"), gameState.score), 1700, 140, 20,BLACK);
}

void PixelGame::PlayerDeath() //muss noch richtig implementiert werden
{
    if (gameState.health <= 0)
    {
        gameState.playerDeath = 1;
        gameState.changeState(MenuState::MainMenu);
    }
}

void PixelGame::ReceiveDmg() //muss noch richtig implementiert werden
{
    if (CheckCollisionRecs(characterRec, lavaRec))
    {
        gameState.health -= gameState.damage_per_frame;
        if (gameState.health <= 0) {
           PlayerDeath();
        }
    }
}


void PixelGame::EnemyInit(Enemy &en, Vector2 positionEnemy, Texture2D &enemyTexture) {
    en.enemyHit = false;
    en.unload = false;
    en.positionEnemy = positionEnemy;
    en.frameRec1 = { 0.0f, 0.0f, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    en.frameRec2 = { 0.0f, (float)enemyTexture.height / 3, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    en.frameRec3 = { 0.0f, ((float)enemyTexture.height / 3) * 2, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    en.currentFrame = 0;
    en.framesCounter = 0;
    en.framesSpeed = 8;
}

void PixelGame::EnemyUpdate(Enemy &en, float deltaTime, Texture2D &enemyTexture) {

    en.framesCounter++;

    if (en.framesCounter >= (60 / en.framesSpeed)) {
        en.framesCounter = 0;
        en.currentFrame++;

        if (en.currentFrame > 20) {
            en.currentFrame = 0;
        }

        en.frameRec1.x = (float)en.currentFrame * (float)enemyTexture.width / 8;
        en.frameRec2.x = (float)en.currentFrame * (float)enemyTexture.width / 8;
        en.frameRec3.x = (float)en.currentFrame * (float)enemyTexture.width / 8;
    }

    if(IsKeyPressed(KEY_SPACE)) {
        en.enemyHit = true;
    }
}

void PixelGame::DrawEnemies(Enemy &en, Texture2D &enemyTexture) {
    if (!en.enemyHit) {
        if(en.currentFrame < 7){
            DrawTextureRec(enemyTexture, en.frameRec1, en.positionEnemy, WHITE);
        } else {
            DrawTextureRec(enemyTexture, en.frameRec2, en.positionEnemy, WHITE);
        }
    } else {
        if(!en.unload) {
            DrawTextureRec(enemyTexture, en.frameRec3, en.positionEnemy, WHITE);
        }
        if(en.currentFrame == 0) {
            UnloadTexture(enemyTexture);
            en.unload = true;
        }

    }
}