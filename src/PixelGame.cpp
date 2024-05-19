#include "PixelGame.h"
#include "Audio.h"
#include "Menu.h"
#include "InGameHud.h"
#include "ApplicationState.h"

ApplicationState gameState;

Texture2D PixelGame::lavaTexture;
Texture2D PixelGame::meatTexture;
Texture2D PixelGame::fruitTexture;

void PixelGame::drawTiles(tson::Map &Map, Texture2D &myTexture)
{
    auto layer1 = Map.getLayer("Kachelebene 2")->getData();
    drawLayer(layer1, Map, myTexture);

    auto layer2 = Map.getLayer("animation")->getData();
    drawLayer(layer2, Map, myTexture);
}

void PixelGame::drawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture)
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

void PixelGame::drawSprite(Texture2D &myTexture, float mcX, float mcY)
{
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle dest = {mcX, mcY, myTexture.width * 0.15f, myTexture.height * 0.15f};

    DrawTexturePro(myTexture, source, dest, {0, 0}, 0.0f, WHITE);
}

void PixelGame::moveCharacter(float& mcX, float& mcY, int direction)
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
    mcX = newPositionX;
    mcY = newPositionY;
}

void PixelGame::gameInit()
{
    Audio::loadResourcesAndInitAudio();
    loadTexture(lavaTexture, "assets/graphics/backgrounds/Lava.png");
    loadTexture(meatTexture, "assets/graphics/Fleisch.png");
    loadTexture(fruitTexture, "assets/graphics/Frucht.png");

    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK) {
        std::cout
                << gameState.getLocalizedText("Failed to parse map, error: ", "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }
}

void PixelGame::gameLoop(tson::Map &Map)
{
    float mcX = 16.0f * 5;
    float mcY = 16.0f * 23;
    bool meatUnload = false;
    bool fruitUnload = false;

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
        ClearBackground(DARKGRAY);

        drawTiles(Map, gameState.myTexture);

        if (!meatUnload) {
            drawTexture(meatTexture, {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f});
        }
        if (!fruitUnload) {
            drawTexture(fruitTexture, {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f});
        }
        drawTexture(lavaTexture, {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f});
        drawSprite(gameState.myMC, mcX, mcY);
        InGameHud::drawHealthBarTexture();
        InGameHud::drawRGBBarTexture();
        gameState.playerDeath = 0;
        DrawText(TextFormat("%s: %i", gameState.getLocalizedText("Score", "Punkte"), gameState.score), 800, 140, 20,
                 BLACK);

        Rectangle characteRec = {mcX, mcY, gameState.myMC.width * 0.15f, gameState.myMC.height * 0.15f};
        Rectangle lavaRec = {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f};
        Rectangle meatRec = {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f};
        Rectangle fruitRec = {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f};

        if (IsKeyPressed(KEY_ESCAPE)) {
            Audio::unloadResourcesAndCloseAudio();
            gameState.changeState(MenuState::PauseMenu);
            return;
        }

        bool isMoving = false;

        if (IsKeyDown(gameState.keyBindings[UP])) {
            moveCharacter(mcX, mcY, KEY_UP);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[DOWN])) {
            moveCharacter(mcX, mcY, KEY_DOWN);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[LEFT])) {
            moveCharacter(mcX, mcY, KEY_LEFT);
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[RIGHT])) {
            moveCharacter(mcX, mcY, KEY_RIGHT);
            isMoving = true;
        }
        if (isMoving && !IsSoundPlaying(gameState.walkingSound)) {
            PlaySound(gameState.walkingSound);
        } else if (!isMoving && IsSoundPlaying(gameState.walkingSound)) {
            StopSound(gameState.walkingSound);
        }
        UpdateMusicStream(gameState.backgroundMusic);

        if (CheckCollisionRecs(characteRec, lavaRec))
        {
            gameState.health -= gameState.damage_per_frame;
            if (gameState.health <= 0) {
                gameState.health = 0;
                Audio::unloadResourcesAndCloseAudio();
                unloadTexture(lavaTexture);
                unloadTexture(meatTexture);
                unloadTexture(fruitTexture);
                gameState.changeState(MenuState::MainMenu);
                gameState.health = 100;
                gameState.playerDeath = 1;
                return;
            }
        }

        if (CheckCollisionRecs(characteRec, meatRec))
        {
            gameState.health += 25;
            if (gameState.health >= 100)
            {
                gameState.health = 100;
            }

            if (!meatUnload)
            {
                unloadTexture(meatTexture);
                meatUnload = true;
                gameState.score += 100;
            }

        }

        if (CheckCollisionRecs(characteRec, fruitRec))
        {
            gameState.health += 15;
            if (gameState.health >= 100) {
                gameState.health = 100;
            }

            if (!fruitUnload)
            {
                unloadTexture(fruitTexture);
                fruitUnload = true;
                gameState.score += 50;
            }
        }

        if (WindowShouldClose())
        {
            CloseWindow();
            Audio::unloadResourcesAndCloseAudio();
            unloadTexture(lavaTexture);
            unloadTexture(fruitTexture);
            unloadTexture(meatTexture);
            exit(0);
        }

        EndDrawing();
    }

    CloseWindow();
    Audio::unloadResourcesAndCloseAudio();
    unloadTexture(lavaTexture);
    unloadTexture(fruitTexture);
    unloadTexture(meatTexture);
}

void PixelGame::loadTexture(Texture2D &texture, const char* path)
{
    texture = LoadTexture(path);
}

void PixelGame::drawTexture(Texture2D &texture, Rectangle dest)
{
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void PixelGame::unloadTexture(Texture2D &texture)
{
    UnloadTexture(texture);
}