/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** pressEnter
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::drawPressEnter()
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/pressEnter.png");

    if (pressEnter.blinkTimer < pressEnter.blinkInterval / 2.0f) {
        pressEnter.posX = (screenW - texture.width * pressEnter.scale) / 2.0f;
        pressEnter.posY = (screenH - texture.height * pressEnter.scale) / 2.0f;
        DrawTextureEx(texture, {pressEnter.posX, pressEnter.posY + 300}, 0.0f, pressEnter.scale, WHITE);
    }
}

void TitleScreenScene::updatePressEnter(float dt)
{
    pressEnter.blinkTimer += dt;
    if (pressEnter.blinkTimer > pressEnter.blinkInterval) {
        pressEnter.blinkTimer -= pressEnter.blinkInterval;
    }
}
