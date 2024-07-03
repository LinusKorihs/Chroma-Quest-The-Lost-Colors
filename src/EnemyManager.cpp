#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    enemies = std::vector<std::shared_ptr<Enemy>>();

}

void EnemyManager::addEnemy(Vector2 position, Texture2D& enemyTexture, EnemyType type, EnemyBehaviour behaviour, EnemyDirection enDirection, float rLimit, float lLimit, float uLimit, float dLimit) {
    enemies.push_back(std::make_shared<Enemy>(position, enemyTexture, type, behaviour, enDirection, rLimit, lLimit, uLimit, dLimit));
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
        if (CheckCollisionRecs(projectile->getRec(), enemy->getRec())) {
            projectile->setActive(false);
            enemy->enemyGetsHit();
            std::cout << getEnemyHits() << std::endl;

            return true;
        }
    }
    return false;
}

Rectangle EnemyManager::getEnemyRec() {
    for (auto& enemy : enemies) {
return enemy->getRec();
}
return Rectangle();
}
Vector2 EnemyManager::getEnemies() {
    for (auto& enemy : enemies) {
        return enemy->getPosition();
    }
    return Vector2();
}
void EnemyManager::EnemyHits() {
    for (auto& enemy : enemies) {
        enemy->enemyGetsHit();
    }
}
int EnemyManager::getEnemyHits() {
    for (auto& enemy : enemies) {
        return enemy->getEnemyHits();
    }
    return 0;
}

void EnemyManager::deleteEnemy() {
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->getUnload()) {
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}
