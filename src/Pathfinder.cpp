
/*
#include "Pathfinder.h"

Pathfinder::Pathfinder(){}

std::vector<Vector2> Pathfinder::findPath(int startX, int startY, int endX, int endY) {
    initPFinding(startX, startY, endX, endY);

    while (!openList.empty()) {
        Node* current = getNextNode();
        std::cout << "Current Node: " << current->x << ", " << current->y << std::endl;
        if (isEndNode(current, endX, endY)) {
            std::cout << "Path found" << std::endl;
            return constructPathAndCleanup(current);
        }
        processNgbrs(current, endX, endY);
    }

    cleanupNodes();
    return std::vector<Vector2>(); // Falls kein Pfad gefunden
}

void Pathfinder::initPFinding(int startX, int startY, int endX, int endY) {
    Node* startNode = new Node(startX, startY, 0, heuristic(startX, startY, endX, endY));
    openList.push(startNode);
    allNodes[startY * mapWidth + startX] = startNode;
}

Node* Pathfinder::getNextNode() {
    Node* current = openList.top();
    std::cout << "openList size: " << openList.size() << std::endl;
    openList.pop();
    std::cout << "openList size: " << openList.size() << std::endl;
    return current;
}

bool Pathfinder::isEndNode(Node* node, int endX, int endY) {
    return node->x == endX && node->y == endY;
}

std::vector<Vector2> Pathfinder::constructPathAndCleanup(Node* endNode) {
    std::vector<Vector2> path = reconstructPath(endNode);
    cleanupNodes();
    endNodeFound = true;
    return path;
}

void Pathfinder::processNgbrs(Node* current, int endX, int endY) {
    for (auto& dir : directions) {
        int newX = current->x + dir[0];
        int newY = current->y + dir[1];

        if (isBlocked(newX, newY)) continue;

        float newG = current->g + 1;
        Node* neighbour = allNodes[newY * mapWidth + newX];
        if (!neighbour) {
            neighbour = new Node(newX, newY, newG, heuristic(newX, newY, endX, endY), current);
            openList.push(neighbour);
            allNodes[newY * mapWidth + newX] = neighbour;
        } else if (newG < neighbour->g) {
            neighbour->g = newG;
            neighbour->parent = current;
            openList.push(neighbour);
        }
    }
}

void Pathfinder::cleanupNodes() {
    for (auto& node : allNodes) {
        delete node.second;
    }
    allNodes.clear();
}

std::vector<Vector2> Pathfinder::reconstructPath(Node* currentNode) {
    std::vector<Vector2> path;

    while (currentNode) {
        Vector2 currentPos = { static_cast<float>(currentNode->x), static_cast<float>(currentNode->y) };
        path.emplace_back(currentPos);
        currentNode = currentNode->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

float Pathfinder::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool Pathfinder::isBlocked(int x, int y) {
    Vector2 point = { static_cast<float>(x), static_cast<float>(y) };

    for (const auto& wall : GameState::wallRectangles) {
        if (CheckCollisionPointRec(point, wall)) {
            return true;
        }
    }

    for (const auto& door : GameState::doorRectangles) {
        if (CheckCollisionPointRec(point, door)) {
            return true;
        }
    }

    if(x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
        return true;
    }

    return false;

}
*/
#include "Pathfinder.h"
#include <iostream>
#include <chrono>

Pathfinder::Pathfinder() {}

std::vector<Vector2> Pathfinder::findPath(int startX, int startY, int endX, int endY) {
    initPFinding(startX, startY, endX, endY);
    int iterationLimit = 1000; // Begrenze die Anzahl der Iterationen
    int iterations = 0;

    while (!openList.empty() && iterations < iterationLimit) {
        Node* current = getNextNode();
        std::cout << "Current Node: " << current->x << ", " << current->y << std::endl;

        if (isEndNode(current, endX, endY)) {
            std::cout << "Path found" << std::endl;
            return constructPathAndCleanup(current);
        }

        processNgbrs(current, endX, endY);
        iterations++;
    }

    std::cout << "Exceeded iteration limit or openList is empty. Iterations: " << iterations << std::endl;
    cleanupNodes();
    return std::vector<Vector2>(); // Falls kein Pfad gefunden
}

void Pathfinder::initPFinding(int startX, int startY, int endX, int endY) {
    while (!openList.empty()) openList.pop(); // Sicherstellen, dass die OpenList leer ist
    cleanupNodes(); // Alle alten Knoten aufräumen

    Node* startNode = new Node(startX, startY, 0, heuristic(startX, startY, endX, endY));
    openList.push(startNode);
    allNodes[startY * mapWidth + startX] = startNode;
}

Node* Pathfinder::getNextNode() {
    Node* current = openList.top();
    openList.pop();
    return current;
}

bool Pathfinder::isEndNode(Node* node, int endX, int endY) {
    return node->x == endX && node->y == endY;
}

std::vector<Vector2> Pathfinder::constructPathAndCleanup(Node* endNode) {
    std::vector<Vector2> path = reconstructPath(endNode);
    cleanupNodes();
    std::cout << "Open list size at cleanup: " << openList.size() << std::endl;
    return path;
}

void Pathfinder::processNgbrs(Node* current, int endX, int endY) {
    for (auto& dir : directions) {
        int newX = current->x + dir[0];
        int newY = current->y + dir[1];

        if (isBlocked(newX, newY)) continue;

        float newG = current->g + 1;
        Node* neighbour = allNodes[newY * mapWidth + newX];
        if (!neighbour) {
            neighbour = new Node(newX, newY, newG, heuristic(newX, newY, endX, endY), current);
            openList.push(neighbour);
            allNodes[newY * mapWidth + newX] = neighbour;
        } else if (newG < neighbour->g) {
            neighbour->g = newG;
            neighbour->parent = current;
            openList.push(neighbour);
        }
    }
}

void Pathfinder::cleanupNodes() {
    for (auto& node : allNodes) {
        delete node.second;
    }
    allNodes.clear();
}

std::vector<Vector2> Pathfinder::reconstructPath(Node* currentNode) {
    std::vector<Vector2> path;

    while (currentNode) {
        Vector2 currentPos = { static_cast<float>(currentNode->x), static_cast<float>(currentNode->y) };
        path.emplace_back(currentPos);
        currentNode = currentNode->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

float Pathfinder::heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool Pathfinder::isBlocked(int x, int y) {
    Vector2 point = { static_cast<float>(x), static_cast<float>(y) };

    for (const auto& wall : currentGameState.wallRectangles) {
        if (CheckCollisionPointRec(point, wall)) {
            return true;
        }
    }

    for (const auto& door : currentGameState.doorRectangles) {
        if (CheckCollisionPointRec(point, door)) {
            return true;
        }
    }

    if(x < 0 || x >= mapWidth || y < 0 || y >= 3296) {
        return true;
    }
    else {
        return false;
    }
}
