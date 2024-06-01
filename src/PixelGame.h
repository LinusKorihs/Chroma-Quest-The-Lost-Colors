#include "raylib.h"
#include "ApplicationState.h"
#include "tileson.h"
#include "stone.h"

struct Projectile {
    Vector2 position;
    Vector2 speed;
    bool isActive;
};

struct Enemy {
    bool enemyHit;
    bool unload;
    Vector2 positionEnemy;
    Rectangle frameRec1;
    Rectangle frameRec2;
    Rectangle frameRec3;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frames;
};

class PixelGame {
public:

    static void DrawTiles(tson::Map &Map, Texture2D &myTexture);
    static void DrawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture);
    static void DrawSprite(Texture2D &myTexture);
    static void MoveCharacter(int direction);
    static void GameInit();
    static void GameLoop(tson::Map &Map);
    static void LoadTextureX(Texture2D &texture, const char* path);
    static void DrawTexture(Texture2D &texture, Rectangle dest);
    static void UnloadTextureX(Texture2D &texture);
    static void DrawObjects();
    static void UnloadAll();
    static void DrawHud();
    static void PlayerDeath();
    static void ReceiveDmg();
    static void Attack();
    static void InitProjectile(Projectile &proj, Vector2 startPosition, Vector2 speed);
    static void UpdateProjectile(Projectile &proj, float deltaTime);
    static void DrawProjectile(const Projectile &proj);
    static void DrawEnemies(Enemy &en, Texture2D &enemyTexture);
    static void EnemyInit(Enemy &en, Vector2 positionEnemy, Texture2D &enemyTexture);
    static void EnemyUpdate(Enemy &en, float deltaTime, Texture2D &enemyTexture);


private:

    static Vector2 position;
    static Camera2D camera;

    static Texture2D lavaTexture;
    static Texture2D meatTexture;
    static Texture2D fruitTexture;
    static Texture2D projectileTexture;
    static Texture2D slimeTexture;
    static Texture2D tilesetTexture;

    static float mcX;
    static float mcY;

    static Rectangle characterRec;
    static Rectangle lavaRec;
    static Rectangle meatRec;
    static Rectangle fruitRec;
    static Rectangle projectileRec;

    static Projectile projectile;
    static Enemy enemy;

    static std::vector <Stone> stones;

};