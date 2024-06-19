#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    enemies = std::vector<std::shared_ptr<Enemy>>();

}

void EnemyManager::addEnemy(Vector2 position, Texture2D& enemyTexture, int hits, float knockbackStrength, EnemyType type) {
    enemies.push_back(std::make_shared<Enemy>(position, enemyTexture, hits, knockbackStrength, type));
}

void EnemyManager::updateEnemies(float deltaTime) {
    for (auto& enemy : enemies) {
        enemy->updateEnemy(deltaTime);
    }
}

void EnemyManager::drawEnemies() {
    for (auto& enemy : enemies) {
        enemy->drawEnemy();
    }
}

bool EnemyManager::checkProjectileEnemyCollision(const std::shared_ptr<Projectile>& projectile, const std::shared_ptr<Enemy>& enemy) {
    for (auto& enemy : enemies) {
        if (CheckCollisionRecs(projectile->getRec(), enemy->getEnemyRec())) {
            enemy->enemyGetsHit();
            projectile->setActive(false);
        }
        return true;
    }
    return false;
}