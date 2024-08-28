
#include "Comments.h"

bool Comments::showedAlready = false;
Texture2D Comments::commentTexture;

Comments::Comments() {
}

void Comments::initComment() {
    commentTexture = TextureManager::getTexture("speechBubble");
}

void Comments::drawComment() {
    DrawTexture(commentTexture, 500, 500, WHITE);
    DrawText("Test", 510, 510, 20, WHITE);
}

