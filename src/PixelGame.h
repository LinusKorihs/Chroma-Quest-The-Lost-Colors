#pragma once

#include "GameState.h"
#include "Audio.h"
#include "Enemy.h"
#include "InGameHud.h"
#include "Menu.h"
#include "Projectile.h"
#include "raylib.h"
#include "Objects.h"
#include "tileson.h"
#include "EnemyManager.h"
#include "MiniBoss.h"
#include "Pathfinder.h"

#include "Comments.h"
#include "DialogBox.h"
#include "NPC.h"

enum gameLoopState
        {
    sequence,
    gameLoopState
};

class MiniBoss;

class PixelGame
{
public:
    static void gameInit();
    static void gameLoop(tson::Map& tileMap);
    static void startSequence();

    static Enemy enemy;
    static Vector2 position;
    static Texture2D slimeEnemyTexture;


    static void runGameOnce(tson::Map &Map);

    static void eraseDoor(int targetX, int targetY);
    static void openDoors();
    static void openBottomDoorRoom1();
    static void closedDoorTransition();
    static void checkPressurePlates();
    static void createEnemies();

    static Pathfinder* pathfinder;
    static MiniBoss* miniboss;

    static void rectangle();

    static void loadMap(const std::string &mapPath);
    static void unloadMap();
    static tson::Map& getMap();
    static void updateAudio();
    static void ReloadAssets(Texture2D &logoTex, RenderTexture &canvas);

    static tson::Map currentMap;
    static bool dialogDone;

    static enum gameLoopState state;

    static bool canMove;
private:
    static void drawObjects();
    static void drawHud();
    static void unloadAll();

    static std::shared_ptr<Projectile> projectile_p;
    static std::shared_ptr<Projectile> projectileEnemy_p;
    //static std::shared_ptr<MiniBoss> miniBoss_p;
    //static std::shared_ptr<Enemy> enemy_p;
    static EnemyManager enemyManager;
    static Texture2D BossRed;
    static Texture2D slimeEnemyTextureRed;
    static Vector2 BossRedPosition;
    static Door door;

    static bool hasAnimated[3];

    static Music music;
    static Music overworldMusic;
    static Music dungeonMusic2;

    static bool track1Played;
    static bool firstLoopOverworld;
    static bool firstLoopDungeon1;
    static int sentence;
    static bool controlBoxWasActive;
    static int dialogCounter;


};

