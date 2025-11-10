/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** msz function
*/

#include "scenes/GameScene.hpp"
#include <sstream>

void Commands::msz(GameScene &gm, std::string params)
{
    int mWidth, mHeight;

    try {
        std::stringstream ss(params);
        ss >> mWidth >> mHeight;
    } catch(...) {
        throw ParamsException("msz: Bad Params");
    }
    std::cout << "MAP SIZE: "<< mWidth << " " << mHeight << std::endl;
    gm.setMapWidth(mWidth);
    gm.setMapHeight(mHeight);
    gm.init_values();
    gm.setLoading(true);
}
