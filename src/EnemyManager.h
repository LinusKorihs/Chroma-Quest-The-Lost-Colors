#ifndef RAYLIBSTARTER_ENEMYMANAGER_H
#define RAYLIBSTARTER_ENEMYMANAGER_H

#include <vector>
#include <memory>
#include "Enemy.h"
#include "Projectile.h"
#include <iostream>

class EnemyManager {

public:
    EnemyManager();

    void addEnemy(Vector2 position, Texture2D& enemyTexture, int hits, float knockbackStrength, EnemyType type);
    void updateEnemies(float deltaTime);
    void drawEnemies();
    Rectangle getEnemyRec();
    Vector2 getEnemies();
    bool checkProjectileEnemyCollision(const std::shared_ptr<Projectile>& projectile, const std::shared_ptr<Enemy>& enemy);
    std::vector<std::shared_ptr<Enemy>> enemies;

private:

    Rectangle enemyRec;
};


#endif //RAYLIBSTARTER_ENEMYMANAGER_H