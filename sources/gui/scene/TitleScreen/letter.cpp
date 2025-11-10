/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** letter
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::drawLetter()
{
    Texture2D &texture = _textureManager->getTexture("resources/titleScreen/letter1.png");
    float posX = letter.baseX +
        sinf(letter.time * 2.0f * PI * letter.oscillationFreq) * letter.oscillationAmp;
    float rot = sinf(letter.time * 2.0f * PI *
        (letter.oscillationFreq / 2.0f)) * letter.rotationAmp;
    Vector2 origin = {texture.width * letter.scale / 2,
        texture.height * letter.scale / 2};

    DrawTextureEx(texture, {posX - origin.x, letter.y - origin.y},
        rot, letter.scale, WHITE);
}

void TitleScreenScene::updateLetter(float dt)
{
    letter.y += letter.speed * dt;
    letter.time += dt;
    if (!letter.isTake && letter.y > screenH + 100) {
        letter.isTake = true;
    }
}
