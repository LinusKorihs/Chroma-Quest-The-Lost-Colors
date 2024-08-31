
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
    void setTargetPosOverworld();
    void overworldTransition();
    void dungeon1Transition();
    void setTargetPos(tson::Map &tileMap);
    bool getDungeon1();
    bool getOverworld();

    bool dungeon1 = true;
    bool overworld = false;

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


