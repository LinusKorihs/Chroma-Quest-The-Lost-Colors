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
            return true;
        }
    }
    return false;
}

Rectangle EnemyManager::getEnemyRec() {
    for (auto& enemy : enemies) {
return enemy->getEnemyRec();
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
    for (auto it = enemies.begin(); it != enemies.end(); /* keine Inkrementierung hier */) {
        if ((*it)->getUnload()) {
            it = enemies.erase(it); // Löscht das Element und gibt den neuen Iterator zurück
        } else {
            ++it; // Inkrementiert den Iterator nur, wenn kein Element gelöscht wurde
        }
    }
}