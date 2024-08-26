#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "DrawMap.h"
#include "GameState.h"

struct Node {
    int x, y;
    float g, h;
    Node* parent; // Vorgänger

    Node(int x, int y, float g, float h, Node* parent = nullptr)
            : x(x), y(y), g(g), h(h), parent(parent) {}

    float getF() const { return g + h; } // Kostensumme
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->getF() > b->getF();
    }
};

class Pathfinder {
public:
    Pathfinder();
    std::vector<Vector2> findPath(int startX, int startY, int endX, int endY);
    void cleanupNodes();
    void processNgbrs(Node* current, int endX, int endY);
    std::vector<Vector2> constructPathAndCleanup(Node* endNode);
    bool isEndNode(Node* node, int endX, int endY);
    Node* getNextNode();
    void initPFinding(int startX, int startY, int endX, int endY);
    bool isBlocked(int x, int y);

private:
    std::vector<Vector2> reconstructPath(Node* currentNode);
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList; // Priority Queue
    std::unordered_map<int, Node*> allNodes;
    float heuristic(int x1, int y1, int x2, int y2);
    int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
    int mapWidth = 79*32;
    int mapHeight = 103*32;
    bool endNodeFound = false;
};