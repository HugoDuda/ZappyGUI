/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GameModel
*/

#ifndef _GAMEMODEL_HPP_
    #define _GAMEMODEL_HPP_

    #include <list>

    #include "network/Team.hpp"
    #include "parser/XMLParser.hpp"

class GameModel
{
    public:
        GameModel(PokemonManager &pokemonManager)
        : _pokemonManager(pokemonManager)
        {}

        Team &createTeam(std::string id, Color color);

        void createPlayer(int pid, std::string tname, position_t pos, int pokeId, animationDirection dir);

        bool removePlayer(int pid);
    
        const std::unordered_map<std::string, std::unique_ptr<Team>> &teams() const;

        void drawAll(std::shared_ptr<TextureManager> textureManager) const;

        const std::list<int> &getlist() const
        {
            return pidList;
        }
        void updateAll(float dt);
        bool movePlayer(int pid, int x, int y, animationDirection dir, int frequency);
        std::shared_ptr<Player> getPlayer(int pid);
        void startIncantations(std::vector<int> pids, int timer);
        void endIncantations(std::vector<int> pids);
        void setEjection(int pid);
    private:
        std::list<int> pidList;
        PokemonManager &_pokemonManager;
        std::unordered_map<std::string, std::unique_ptr<Team>> _teams;
        std::list<std::pair<int, int>> incantationTiles;
};

#endif
