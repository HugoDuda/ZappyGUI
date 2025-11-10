/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** freq
*/

#include "HUD.hpp"

void HUD::freq(int freq, float elapsedTimeFreq)
{
    if (elapsedTimeFreq < 1.f) {
        DrawTextureEx(_textureManager->getTexture("resources/freqHUD.png"), {566, 50}, 0.f, 1.5f, WHITE);
        _textManager->drawText("Frequence", {666, 74}, 48.f);
        _textManager->drawText("Actual : " + std::to_string(freq), {641, 174}, 48.f);
    }
}
