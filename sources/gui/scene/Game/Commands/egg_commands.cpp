/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** enw function
*/

#include "scenes/GameScene.hpp"
#include <sstream>
#include <set>

void Commands::enw(GameScene &gm, std::string params)
{
    std::string tname, pid;
    int x, y;
    int val = 0;
    std::set<int> excluded = {512, 514, 516, 520, 522, 523, 538, 539, 558, 564,
    565, 580, 588, 591, 592, 594, 599, 600, 601, 616, 617, 626, 660, 668, 712,
    713, 731, 732, 733, 734, 735, 741, 748, 750, 756, 765, 775, 819, 820, 832,
    834, 836, 837, 838, 839, 847, 863, 866, 870, 878, 889, 893, 896};
    int id = 1;

    try {
        std::stringstream ss(params);
        ss >> tname >> pid >> x >> y;
    } catch(...) {
        throw ParamsException("enw: Bad Params");
    }
    try {
        val = std::stoi(pid);
    } catch (...) {
        return;
    }
    do {
        id = rand() % 899 + 1;
    } while (excluded.count(id));
    gm.getGameModel()->createPlayer(val, tname, {x, y}, id, animationDirection::South);
}

void Commands::ebo(GameScene &gm, std::string params)
{
    std::string tname, pid;

    try {
        std::stringstream ss(params);
        ss >> tname >> pid;
    } catch(...) {
        throw ParamsException("ebo: Bad Params");
    }
    (void)gm;
    // egg hatching to a player
}

void Commands::edi(GameScene &gm, std::string params)
{
    std::string tname, pid;

    try {
        std::stringstream ss(params);
        ss >> tname >> pid;
    } catch(...) {
        throw ParamsException("edi: Bad Params");
    }
    (void)gm;
    // egg dead without player connection
}
