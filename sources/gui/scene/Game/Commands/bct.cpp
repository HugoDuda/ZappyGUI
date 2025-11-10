/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** bct function
*/

#include "scenes/GameScene.hpp"
#include <sstream>

void Commands::bct(GameScene &gm, std::string params)
{
    int x = 0, y = 0, food = 0, line = 0, derau = 0, sib = 0, mend = 0, phir = 0, thyst = 0;

    try {
        std::stringstream ss(params);
        ss >> x >> y >> food >> line >> derau >> sib >> mend >> phir >> thyst;
    } catch(...) {
        throw ParamsException("bct: Bad Params");
    }
    gm.setTileContent(x, y, food, line, derau, sib, mend, phir, thyst);
}
