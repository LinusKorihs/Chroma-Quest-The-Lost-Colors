
#pragma once
#include "raylib.h"
#include "MainCharacter.h"

class RoomChanger {
public:
    RoomChanger();
    void update();
    void startTransition(Vector2 newPosition);
    bool isTransitioning() const;
    Vector2 getTargetPos();
    void setTargetPos();
    void setTargetPos(tson::Map &tileMap);

private:
    enum TransitionPhase {
        None,
        Darkening,
        Black,
        Brightening
    };

    TransitionPhase phase;
    float transitionProgress;
    Vector2 targetPosition;
    void drawTransitionEffect() const;
};


