
#pragma once
#include "raylib.h"
#include "MainCharacter.h"

class RoomChanger {
public:
    RoomChanger();
    void update();
    void startTransition(int newRoom, Vector2 newPosition);
    bool isTransitioning() const;

private:
    enum class TransitionPhase {
        None,
        Darkening,
        Black,
        Brightening,
        WAIT
    };

    TransitionPhase phase;
    float transitionProgress;
    int targetRoom;
    Vector2 targetPosition;
    void drawTransitionEffect() const;
};


