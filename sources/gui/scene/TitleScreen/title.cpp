/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** title
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::drawTitle()
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/title.png");

    float posX = (screenW - texture.width * title.scale) / 2.0f;
    float posY = (screenH - texture.height * title.scale) / 2.0f;
    DrawTextureEx(texture, {posX, posY - 100}, 0.0f, title.scale, WHITE);
}
