/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** TitleScreenScene
*/

#include "scenes/TitleScreenScene.hpp"

TitleScreenScene::TitleScreenScene
(std::shared_ptr<TextureManager> textureManager)
: AScene(textureManager, nullptr, true)
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/bekipan.png");

    letter.baseX = screenW * 0.75f;
    bekipan.x = screenW + 32;
    bekipan.y = screenH * 0.15f;
    bekipan.frame = 0;
    bekipan.animTimer = 0.f;
    bekipan.currentDuration = bekipan.frameDurations[0];
    closeUpBekipan.start = {(float)screenW + 60, (float)screenH - texture.height};
    closeUpBekipan.end = {-texture.width * closeUpBekipan.endScale, screenH * 0.05f};
}
