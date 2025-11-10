/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** tna function
*/

#include "scenes/GameScene.hpp"

void Commands::tna(GameScene &gm, std::string params)
{
    if (params.empty() || params.size() > 30) {
        throw ParamsException("tna: Go fuck yourself.");
    }

    params.erase(0, params.find_first_not_of(" \t"));
    if (params.find_last_not_of(" \t") == params.npos) {
        throw ParamsException("tna: multiples parameters.");
    }
    std::cout << "new team: " << params << std::endl;
    gm.getGameModel()->createTeam(
        params, {
            static_cast<unsigned char>(rand() % 255),
            static_cast<unsigned char>(rand() % 255),
            static_cast<unsigned char>(rand() % 255),
            255
        }
    );
}
