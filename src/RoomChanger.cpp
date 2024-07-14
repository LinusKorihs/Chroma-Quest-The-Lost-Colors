#include "RoomChanger.h"
#include "MainCharacter.h"

RoomChanger::RoomChanger()
        : phase(TransitionPhase::None), transitionProgress(0.0f), targetPosition({0, 0}) {}

void RoomChanger::update() {
    if (phase != TransitionPhase::None) {
        transitionProgress += 0.02f; //transutuon speed

        switch (phase) {
            case TransitionPhase::Darkening:
                if (transitionProgress >= 0.5f) {
                    transitionProgress = 0.5;
                    phase = TransitionPhase::Black;
                }
                break;
            case TransitionPhase::Black:
                MainCharacter::setPosition(targetPosition);
                if(MainCharacter::playerPosX == targetPosition.x && MainCharacter::playerPosY == targetPosition.y)
                {
                    phase = TransitionPhase::Brightening;
                }
                break;
            case TransitionPhase::Brightening:
                if (transitionProgress >= 1.4f) {
                    phase = TransitionPhase::None;
                }
                break;
            default:
                break;
        }

        drawTransitionEffect();
    }
}

void RoomChanger::startTransition(Vector2 newPosition) {
    phase = TransitionPhase::Darkening;
    transitionProgress = 0.0f;
    targetPosition = newPosition;
}

bool RoomChanger::isTransitioning() const { //true wenn phase != none
    return phase != TransitionPhase::None;
}

void RoomChanger::drawTransitionEffect() const {
    float alpha = 0.0f;
    if (phase == TransitionPhase::Darkening) {
        alpha = transitionProgress;
    } else if (phase == TransitionPhase::Black) {
        alpha = 1.0f;
    } else if (phase == TransitionPhase::Brightening) {
        alpha = 1.0f - (transitionProgress - 0.2f);
    }
    DrawRectangle(0, 0, 2500, 3000,
                  Fade(BLACK, alpha));
}

Vector2 RoomChanger::getTargetPos()
{
    return targetPosition;
}

void RoomChanger::setTargetPos()
{
    if(MainCharacter::playerPosX < 38*32 && MainCharacter::playerPosX > 33*32 &&  65*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 62*32)
    {
        targetPosition = {1120, 2194};
    }

    if(MainCharacter::playerPosX > 39*32 && MainCharacter::playerPosX < 42*32 &&  58*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 54*32)
    {
        targetPosition = {45*32+18, 56*32};
    }
    if(MainCharacter::playerPosX > 44*32 && MainCharacter::playerPosX < 47*32 &&  57*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 55*32)
    {
        targetPosition = {41*32-18, 56*32};
    }

    if(MainCharacter::playerPosX > 32*32 && MainCharacter::playerPosX < 38*32 &&  50*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 47*32)
    {
        targetPosition = {35*32, 21*32-18};
    }
    if(MainCharacter::playerPosX > 33*32 && MainCharacter::playerPosX < 37*32 &&  22*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 19*32)
    {
        targetPosition = {35*32, 48*32+18};
    }

    if(MainCharacter::playerPosX > 28*32 && MainCharacter::playerPosX < 31*32 &&  58*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 54*32)
    {
        targetPosition = {25*32-18, 56*32};
    }
    if(MainCharacter::playerPosX > 23*32 && MainCharacter::playerPosX < 26*32 &&  57*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 55*32)
    {
        targetPosition = {29*32+18, 56*32};
    }

    if(MainCharacter::playerPosX > 13*32 && MainCharacter::playerPosX < 15*32 &&  53*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 50*32)
    {
        targetPosition = {14*32, 47*32-18};
    }
    if(MainCharacter::playerPosX > 13*32 && MainCharacter::playerPosX < 15*32 &&  48*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 45*32)
    {
        targetPosition = {14*32, 51*32+18};
    }

    if(MainCharacter::playerPosX > 32*32 && MainCharacter::playerPosX < 35*32 &&  29*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 27*32)
    {
        targetPosition = {38*32+18, 28*32};
    }
    if(MainCharacter::playerPosX > 37*32 && MainCharacter::playerPosX < 40*32 &&  30*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 27*32)
    {
        targetPosition = {34*32-18, 28*32};
    }

    if(MainCharacter::playerPosX > 46*32 && MainCharacter::playerPosX < 49*32 &&  37*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 35*32)
    {
        targetPosition = {52*32+18, 36*32};
    }
    if(MainCharacter::playerPosX > 51*32 && MainCharacter::playerPosX < 54*32 &&  37*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 35*32)
    {
        targetPosition = {48*32-18, 36*32};
    }

    if(MainCharacter::playerPosX > 60*32 && MainCharacter::playerPosX < 63*32 &&  48*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 45*32)
    {
        targetPosition = {61*32, 51*32+18};
    }
    if(MainCharacter::playerPosX > 60*32 && MainCharacter::playerPosX < 63*32 &&  53*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 50*32)
    {
        targetPosition = {61*32, 47*32-18};
    }


}