#include "ApplicationState.h"
#include "Audio.h"
#include "cmath"
#include "InGameHud.h"
#include <memory>
#include "Menu.h"
#include "Projectile.h"
#include "raylib.h"
#include "stone.h"
#include "tileson.h"



/*struct Projectile {
    Vector2 position;
    Vector2 speed;
    bool isActive;
    float projDest;
};
*/
struct Enemy {
    bool enemyHit;
    int enemyHits;
    bool turnAround;
    bool unload;
    Vector2 positionEnemy;
    Rectangle frameRec1;
    Rectangle frameRec2;
    Rectangle frameRec3;
    Rectangle enemyRec;
    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int frames;
    float knockbackStrength;
    Vector2 knockbackDirection;
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
    static void ReceiveDmg(Enemy &en);
    static void Attack();
    //static void InitProjectile(Projectile &proj, Vector2 startPosition, Vector2 speed);
    //static void UpdateProjectile(Projectile &proj, float deltaTime);
    //static void DrawProjectile(const Projectile &proj);
    static void DrawEnemies(Enemy &en, Texture2D &enemyTexture);
    static void EnemyInit(Enemy &en, Vector2 positionEnemy, Texture2D &enemyTexture);
    static void EnemyUpdate(Enemy &en, float deltaTime, Texture2D &enemyTexture);
    //static void ProjectileCollision(Projectile &proj);
    static int GetProjDest();


private:

    static Vector2 position;
    static Camera2D camera;

    static Texture2D lavaTexture;
    static Texture2D meatTexture;
    static Texture2D fruitTexture;
    //static Texture2D projectileTexture;
    static Texture2D slimeTexture;
    static Texture2D tilesetTexture;

    static float mcX;
    static float mcY;
    static int projDest;

    static bool lastDirectionLeft;
    static bool lastDirectionUp;
    static bool lastDirectionRight;
    static bool lastDirectionDown;
    static bool isKnocked;

    static Rectangle characterRec;
    static Rectangle lavaRec;
    static Rectangle meatRec;
    static Rectangle fruitRec;
    //static Rectangle projectileRec;

    //static Projectile projectile;
    static Enemy enemy;

    static std::vector <Stone> stones;

    static std::shared_ptr<Pixelgame::Projectile> proj_p;

};