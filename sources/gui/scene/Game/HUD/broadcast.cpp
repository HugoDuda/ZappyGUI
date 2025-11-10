/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** broadcast
*/

#include "HUD.hpp"
#include <algorithm>

void HUD::broadcast()
{
    Texture2D &infoInterface = _textureManager->getTexture("resources/infoInterface.png");

    if (displayInfoInterface) {
        DrawTextureEx(infoInterface, {286.f, 800.f}, 0.0f, 1.5f, WHITE);
        int n = std::min(3, (int)_messages.size());
        for (int i = 0; i < n; ++i) {
            std::string message = _messages[_messages.size() - n + i];
            std::replace(message.begin(), message.end(), '_', ' ');
            _textManager->drawCode("PLAYER", {350.f, 840.f + 60.f * i}, 50.f, message);
        }
    }
}
