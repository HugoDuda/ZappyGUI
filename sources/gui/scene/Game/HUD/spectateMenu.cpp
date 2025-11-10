/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** spectateMenu
*/

#include "HUD.hpp"
#include <iostream>

std::string HUD::formatPokemonId(int pokemonId)
{
    return (pokemonId < 10) ? "000" + std::to_string(pokemonId) :
    (pokemonId < 100) ? "00" + std::to_string(pokemonId) :
    "0" + std::to_string(pokemonId);
}

void HUD::spectateMenu(const std::string &playerName, const std::string &level,
    const std::string &teamName, int pid, std::array<int, 7> inventory, bool isIncantation)
{
    Texture2D &menuInterface = _textureManager->getTexture("resources/playerData.png");
    float offset = 0.f;

    if (displayMenuInterface) {
        DrawTextureEx(menuInterface, {80.f, 45.f}, 0.0f, 3.6f, WHITE);
        _textManager->drawCode("PLAYER", {150.f, 100.f}, 50.f, " ID : " + playerName);
        _textManager->drawCode("LEVEL", {150.f, 160.f}, 50.f, " : " + level);
        _textManager->drawCode("TEAM", {150.f, 220.f}, 50.f, " : " + teamName);
        if (isIncantation) {
            offset = 40.f;
        }
        if (inventory[0] <= 10) {
            offset = 80.f;
        }
        DrawTexturePro(_textureManager->getTexture("resources/portrait/" + formatPokemonId(pid) + ".png"),
            {0.f + offset, 0.f, 40.f, 40.f}, {200.f, 310.f, 40.f * 5.f, 40.f * 5.f}, {0.f, 0.f}, 0.f, WHITE);
        DrawTextureEx(menuInterface, {1400.f, 45.f}, 0.0f, 3.6f, WHITE);
        _textManager->drawText("Food x" + std::to_string(inventory[0]), {1470.f, 100.f}, 50.f);
        _textManager->drawText("Linemate x" + std::to_string(inventory[1]), {1470.f, 160.f}, 50.f);
        _textManager->drawText("Deraumere x" + std::to_string(inventory[2]), {1470.f, 220.f}, 50.f);
        _textManager->drawText("Sibur x" + std::to_string(inventory[3]), {1470.f, 280.f}, 50.f);
        _textManager->drawText("Mendiane x" + std::to_string(inventory[4]), {1470.f, 340.f}, 50.f);
        _textManager->drawText("Phiras x" + std::to_string(inventory[5]), {1470.f, 400.f}, 50.f);
        _textManager->drawText("Thystame x" + std::to_string(inventory[6]), {1470.f, 460.f}, 50.f);
    }
}
