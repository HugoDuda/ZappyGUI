/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** player related functions
*/

#include "scenes/GameScene.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

/*
    TODO/GUI/DONE
            pnw #n X Y O L N\n connection of a new player
            ppo #n X Y O\n ppo #n\n player’s position
            plv #n L\n plv #n\n player’s level
        pin #n X Y q0 q1 q2 q3 q4 q5 q6\n pin #n\n player’s inventory
        pex #n\n expulsion
        pbc #n M\n broadcast
        pic X Y L #n #n . . . \n start of an incantation (by the first player)
        pie X Y R\n end of an incantation
        pfk #n\n egg laying by the player
        pdr #n i\n resource dropping
        pgt #n i\n resource collecting
            pdi #n\n death of a player
*/

static animationDirection getDirection(int direction)
{
    if (direction == 1)
        return animationDirection::North;
    if (direction == 2)
        return animationDirection::East;
    if (direction == 3)
        return animationDirection::South;
    return animationDirection::West;
}

void Commands::pnw(GameScene& gm, std::string params)
{
    int pid = 0, x = 0, y = 0, direction = 0, lvl = 0;
    std::string pid_string, tname;
    std::set<int> excluded = {512, 514, 516, 520, 522, 523, 538, 539, 558, 564,
    565, 580, 588, 591, 592, 594, 599, 600, 601, 616, 617, 626, 660, 668, 712,
    713, 731, 732, 733, 734, 735, 741, 748, 750, 756, 765, 775, 819, 820, 832,
    834, 836, 837, 838, 839, 847, 863, 866, 870, 878, 889, 893, 896};
    int id = 1;

    do {
        id = rand() % 899 + 1;
    } while (excluded.count(id));
    try {
        std::stringstream ss(params);
        ss >> pid_string >> x >> y >> direction >> lvl >> tname;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pnw: Bad Params");
    }
    gm.getGameModel()->createPlayer(
        pid,
        tname,
        (position_t){
            (int)gm.convertPositionX((float)x),
            (int)gm.convertPositionY((float)y)
        },
        id,
        getDirection(direction)
    );
    std::cout << "NEW PLAYER #"<< pid << " (Skin id = #" << id << ") at x: " << x << ", y: " << y << std::endl; 
}

void Commands::ppo(GameScene& gm, std::string params)
{
    int pid = 0, x = 0, y = 0, direction = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> x >> y >> direction;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("ppo: Bad Params");
    }
    gm.getGameModel()->movePlayer(
        pid,
        gm.convertPositionX(x),
        gm.convertPositionY(y),
        getDirection(direction),
        gm.getFrequency()
    );
}

void Commands::plv(GameScene& gm, std::string params)
{
    int pid = 0, lvl = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> lvl;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pdi: Bad Params");
    }
    std::cout << "Player #" << pid << " leveled up: " << lvl << std::endl;
    auto player = gm.getGameModel()->getPlayer(pid);
    player->setPlayerLvl((unsigned char)lvl);
}

void Commands::pin(GameScene& gm, std::string params)
{
    int x = 0, y = 0, food = 0, line = 0, derau = 0, sib = 0, mend = 0, phir = 0, thyst = 0;
    int pid = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> x >> y >> food >> line >> derau >> sib >> mend >> phir >> thyst;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pin: Bad Params");
    }
    gm.getGameModel()->getPlayer(pid)->setInventory(food, line, derau, sib, mend, phir, thyst);
}

void Commands::pex(GameScene& gm, std::string params)
{
    int pid = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pex: Bad Params");
    }
    gm.getGameModel()->setEjection(pid);
}

void Commands::pbc(GameScene& gm, std::string params)
{
    int pid = 0;
    std::string pid_string, message;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> message;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pbc: Bad Params");
    }
    gm.getGameModel()->getPlayer(pid)->startBroadcast(gm.getFrequency());
    gm.addBrodcast(pid, message);
}

void Commands::pic(GameScene& gm, std::string params)
{
    int x = 0, y = 0, lvl = 0;
    std::vector<int> pids;
    std::stringstream ss(params);
    char hash = 0;
    int pid = 0;

    if (!(ss >> x >> y >> lvl)) {
        throw ParamsException("pic: Bad Params");
    }
    for (;;) {
        try {
            if (!(ss >> hash >> pid) || hash != '#') {
                throw ParamsException("pic: Bad PID format");
            }
            pids.push_back(pid);
        } catch (...) {
            break;
        }
    }
    gm.getGameModel()->startIncantations(pids, gm.getFrequency());
}

void Commands::pie(GameScene& gm, std::string params)
{
    int x = 0, y = 0, result;

    try {
        std::stringstream ss(params);
        ss >> x >> y >> result;
    } catch(...) {
        throw ParamsException("pie: Bad Params");
    }
    (void)gm;
}

void Commands::pfk(GameScene& gm, std::string params)
{
    int pid = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pfk: Bad Params");
    }
    gm.getGameModel()->getPlayer(pid)->startFork(gm.getFrequency());
}

void Commands::pdr(GameScene& gm, std::string params)
{
    int pid = 0, r_id = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> r_id;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pdr: Bad Params");
    }
    std::shared_ptr<Player> player = gm.getGameModel()->getPlayer(pid);
    // player->removeItem(r_id);
}

void Commands::pgt(GameScene& gm, std::string params)
{
    int pid = 0, r_id = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string >> r_id;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pgt: Bad Params");
    }
    std::shared_ptr<Player> player = gm.getGameModel()->getPlayer(pid);
    // player->addItem(r_id);
}

void Commands::pdi(GameScene& gm, std::string params)
{
    int pid = 0;
    std::string pid_string;

    try {
        std::stringstream ss(params);
        ss >> pid_string;
        pid_string.erase(pid_string.find("#"), 1);
        pid = atoi(pid_string.c_str());
    } catch(...) {
        throw ParamsException("pdi: Bad Params");
    }
    std::cout << "Player #" << pid << " died." << std::endl;
    gm.getGameModel()->removePlayer(pid);
}
