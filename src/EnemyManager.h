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

    void addEnemy(Vector2 position, Texture2D& enemyTexture, EnemyType type, EnemyBehaviour behaviour, EnemyDirection enDirection);
    void updateEnemies(float deltaTime);
    void drawEnemies();
    void deleteEnemy();
    Rectangle getEnemyRec();
    Vector2 getEnemies();
    void EnemyHits();
    int getEnemyHits();
    bool checkProjectileEnemyCollision(const std::shared_ptr<Projectile>& projectile, const std::shared_ptr<Enemy>& enemy);
    std::vector<std::shared_ptr<Enemy>> enemies;

private:

    Rectangle enemyRec;
};


#endif //RAYLIBSTARTER_ENEMYMANAGER_H