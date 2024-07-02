#include "RoomChanger.h"

RoomChanger::RoomChanger()
        : phase(TransitionPhase::None), transitionProgress(0.0f), targetRoom(0), targetPosition({0, 0}) {}

void RoomChanger::update() {
    if (phase != TransitionPhase::None) {
        transitionProgress += 0.02f; //transutuon speed

        switch (phase) {
            case TransitionPhase::WAIT:
                phase = TransitionPhase::Brightening;
                transitionProgress = 0.3f;
                break;
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
                    phase = TransitionPhase::WAIT;
                }
                //phase = TransitionPhase::Brightening;
                transitionProgress = 1.3f;
                break;
            case TransitionPhase::Brightening:
                transitionProgress += 0.01f;
                if (transitionProgress >= 1.5f) {
                    transitionProgress = 1.5f;
                    phase = TransitionPhase::None;
                }
                break;
            default:
                break;
        }

        drawTransitionEffect();
    }
}

void RoomChanger::startTransition(int newRoom, Vector2 newPosition) {
    phase = TransitionPhase::Darkening;
    transitionProgress = 0.0f;
    targetRoom = newRoom;
    targetPosition = newPosition;
}

bool RoomChanger::isTransitioning() const {
    return phase != TransitionPhase::None;
}

void RoomChanger::drawTransitionEffect() const {
    float alpha = 0.0f;
    if (phase == TransitionPhase::Darkening) {
        alpha = transitionProgress;
    } else if (phase == TransitionPhase::Black) {
        alpha = 1.0f;
    } else if (phase == TransitionPhase::WAIT) {
        alpha = 1.0f;
    } else if (phase == TransitionPhase::Brightening) {
        alpha = 1.0f - (transitionProgress - 0.2f);
    }
    DrawRectangle(0, 0, 2000, 3000, Fade(BLACK, alpha)); //W/H müssen noch genauer werden - ist nur ein random großes rec
}
