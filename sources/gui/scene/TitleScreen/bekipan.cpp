/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** bekipan
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::drawBekipan()
{
    int frameX = bekipan.frame * bekipan.frameWidth;
    int frameY = 6 * bekipan.frameHeight;
    Rectangle src = {
        (float)frameX, (float)frameY,
        (float)bekipan.frameWidth, (float)bekipan.frameHeight
    };
    Rectangle dst = {
        bekipan.x, bekipan.y,
        bekipan.frameWidth * bekipan.scale,
        bekipan.frameHeight * bekipan.scale
    };

    if (bekipan.x > -100) {
        DrawTexturePro(_textureManager->getTexture("resources/pokemon_sprites/0279/Walk-Anim.png"), src, dst, {0.f, 0.f}, 0.f, WHITE);
    }
}

void TitleScreenScene::updateBekipan(float dt)
{
    bekipan.animTimer += dt * 60.f;
    if (bekipan.animTimer >= bekipan.currentDuration) {
        bekipan.animTimer = 0.f;
        bekipan.frame = (bekipan.frame + 1) % bekipan.frameCount;
        bekipan.currentDuration = bekipan.frameDurations[bekipan.frame];
    }
    bekipan.x -= bekipan.speed * dt;
    if (!closeUpBekipan.active && bekipan.x < -350 && !closeUpBekipan.done) {
        closeUpBekipan.active = true;
        closeUpBekipan.timer = 0.f;
    }
}
