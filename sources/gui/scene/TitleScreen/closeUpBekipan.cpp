/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** closeUpBekipan
*/

#include "scenes/TitleScreenScene.hpp"
#include <algorithm>

void TitleScreenScene::drawCloseUpBekipan()
{
    if (!closeUpBekipan.active && !closeUpBekipan.done)
        return;
    DrawTextureEx(_textureManager->getTexture("resources/titleScreen/bekipan.png"), closeUpBekipan.currentPos, 0.f,
    closeUpBekipan.currentScale, WHITE);
}

void TitleScreenScene::updateCloseUpBekipan(float dt)
{
    float t = 0;

    if (closeUpBekipan.active) {
        closeUpBekipan.timer += dt;
        t = std::clamp(closeUpBekipan.timer / closeUpBekipan.duration, 0.f, 1.f);
        closeUpBekipan.currentPos = {closeUpBekipan.start.x +
            (closeUpBekipan.end.x - closeUpBekipan.start.x) * t, closeUpBekipan.start.y +
            (closeUpBekipan.end.y - closeUpBekipan.start.y) * t};
        closeUpBekipan.currentScale = closeUpBekipan.startScale +
            (closeUpBekipan.endScale - closeUpBekipan.startScale) * t;
        if (t >= 1.f) {
            closeUpBekipan.active = false;
            closeUpBekipan.done = true;
        }
        if (t >= 0.35f) {
            letter.isTake = true;
        }
    }
}
