/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Background
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::drawBackground()
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/background.png");

    float scale = (float)screenH / texture.height;
    float displayedWidth = texture.width * scale;
    float scrollMod = fmod(background.scroll, displayedWidth);

    for (float x = -scrollMod; x < screenW; x += displayedWidth) {
        DrawTextureEx(texture, {x, 0.f}, 0.0f, scale, WHITE);
    }
}

void TitleScreenScene::updateBackground(float dt)
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/background.png");
    float scale = (float)screenH / texture.height;
    float displayedWidth = texture.width * scale;

    background.scroll += background.scrollSpeed * dt;
    if (background.scroll >= displayedWidth) {
        background.scroll -= displayedWidth;
    } 
}
