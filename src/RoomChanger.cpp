#include "RoomChanger.h"
#include "MainCharacter.h"

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
    DrawRectangle(0, 0, 2500, 3000, Fade(BLACK, alpha)); //W/H müssen noch genauer werden - ist nur ein random großes rec
}

Vector2 RoomChanger::getTargetPos()
{
    return targetPosition;
}

void RoomChanger::setTargetPos()
{

    if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 900 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1610)
    {
        targetPosition = {846, 1632};
    }
    if(MainCharacter::playerPosX > 830 && MainCharacter::playerPosX < 870 &&  1640 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1625)
    {
        targetPosition = {1009, 1632};
    }

    if(MainCharacter::playerPosX < 745 && MainCharacter::playerPosX > 690 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {704, 1456};
    }
    if(MainCharacter::playerPosX < 745 && MainCharacter::playerPosX > 690 &&  1500 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1400)
    {
        targetPosition = {704, 1618};
    }

    if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 1020 &&  990 > MainCharacter::playerPosY && MainCharacter::playerPosY > 960)
    {
        targetPosition = {1024, 1138};
    }
    if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 1020 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1100)
    {
        targetPosition = {1024, 976};
    }

    if(MainCharacter::playerPosX < 1335 && MainCharacter::playerPosX > 1315 &&  2000 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1490, 1184};
    }
    if(MainCharacter::playerPosX < 1500 && MainCharacter::playerPosX > 1475 &&  2000 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1326, 1184};
    }

    if(MainCharacter::playerPosX < 1780 && MainCharacter::playerPosX > 1760 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1944, 1184};
    }
    if(MainCharacter::playerPosX < 1940 && MainCharacter::playerPosX > 1920 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1768, 1184};
    }

    if(MainCharacter::playerPosX < 1640 && MainCharacter::playerPosX > 1620 &&  1345 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1310)
    {
        targetPosition = {1632, 1494};
    }
    if(MainCharacter::playerPosX < 1640 && MainCharacter::playerPosX > 1620 &&  1500 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1470)
    {
        targetPosition = {1632, 1326};
    }

    if(MainCharacter::playerPosX < 1400 && MainCharacter::playerPosX > 1380 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1230, 1632};
    }
    if(MainCharacter::playerPosX < 1260 && MainCharacter::playerPosX > 1225 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1393, 1632};
    }

    if(MainCharacter::playerPosX < 1450 && MainCharacter::playerPosX > 1435 &&  1640 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1440, 1536};
    }

    if(MainCharacter::playerPosX < 1325 && MainCharacter::playerPosX > 1270 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1166, 1376};
    }
    if(MainCharacter::playerPosX < 1175 && MainCharacter::playerPosX > 1155 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1298, 1376};
    }

    if(MainCharacter::playerPosX < 1100 && MainCharacter::playerPosX > 1060 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {904, 1376};
    }
    if(MainCharacter::playerPosX < 940 && MainCharacter::playerPosX > 860 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1072, 1376};
    }

}