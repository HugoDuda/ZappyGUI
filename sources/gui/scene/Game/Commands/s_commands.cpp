/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** sgt function
*/

#include "network/Socket.hpp"
#include "scenes/GameScene.hpp"
#include <memory>
#include <sstream>

/*
    sgt T\n sgt\n time unit request
    sst T\n sst T\n time unit modification
    seg N\n end of game
*/

void Commands::sgt(GameScene &gm, std::string params)
{
    int timer;

    try {
        std::stringstream ss(params);
        ss >> timer;
    } catch(...) {
        throw ParamsException("msz: Bad Params");
    }
    gm.setFrequency(timer);
}

void Commands::sst(GameScene &gm, std::string timer)
{
    std::unique_ptr<SocketClass>& soc = gm.getSocket();

    soc->pushOutputBuffer("sst " + timer + "\n");
    soc->socketSend();
}

void Commands::seg(GameScene &gm, std::string params)
{
    std::string tname;

    try {
        std::stringstream ss(params);
        ss >> tname;
    } catch(...) {
        throw ParamsException("seg: Bad Params");
    }
    gm.end(tname);
}
