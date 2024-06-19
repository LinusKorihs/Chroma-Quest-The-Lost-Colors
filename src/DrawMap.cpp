#include "DrawMap.h"
#include "GameState.h"

void DrawMap::drawTiles(tson::Map &gameMap, Texture2D &tileTexture)
{
    auto layer1 = gameMap.getLayer("Black")->getData();
    drawLayer(layer1, gameMap, tileTexture);

    auto layer2 = gameMap.getLayer("Kachelebene 1")->getData();
    drawLayer(layer2, gameMap, tileTexture);

    auto layer3 = gameMap.getLayer("Kachelebene 2")->getData();
    drawLayer(layer3, gameMap, tileTexture);

    auto layer4 = gameMap.getLayer("Schatten")->getData();
    //drawLayer(layer4, gameMap, tileTexture);

/*
    auto layer1 = gameMap.getLayer("Kachelebene 2")->getData();
    drawLayer(layer1, gameMap, tileTexture);

    auto layer2 = gameMap.getLayer("animation")->getData();
    drawLayer(layer2, gameMap, tileTexture); */
}

void DrawMap::drawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &tileTexture)
{
    const int currentFrame = int(GetTime() * 6) % 4;
    int multiplier = 1;

    float tileWidth = 32; // Old 16x16
    int tileSetColumns = 8; // Old 16;

    for (int y = 0; y < Map.getSize().y; y++)
    {
        for (int x = 0; x < Map.getSize().x; x++)
        {
            int data = layer[y * Map.getSize().x + x];

            tson::Tileset* tileset = Map.getTilesetByGid(data); // Get the tile from the tileset
            if (tileset != nullptr) //TODO this has to be moved to happen ONCE on map load
            {
                tson::Tile* tile = tileset->getTile(data);

                if (tile != nullptr && tile->get<bool>("Wall")) // Check if the tile is a wall
                {
                    Rectangle wallRec = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier}; // Create a Rectangle for the tile and add it to the list of wall rectangles
                    currentGameState.wallRectangles.push_back(wallRec);
                }
            }

            data--;
            if (data < 0) continue;

            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle destination = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier};

            if (data >= 0xE0) //animation layer
            {
                source.x += (float) (currentFrame * tileWidth);
            }
            DrawTexturePro(tileTexture, source, destination, {0, 0}, 0, WHITE);
            //std::cout << currentGameState.wallRectangles.size() << std::endl;
        }
    }
}