/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Team
*/

#include "network/Player.hpp"
#include <iostream>

#ifndef _TEAM_HPP_
    #define _TEAM_HPP_

class Team
{
    public:
        Team(std::string id, Color color)
        : _id(id), _color(color)
        {}

        std::string getId() const
        {
            return _id;
        }

        Color getColor() const
        {
            return _color;
        }

        void addPlayer(std::shared_ptr<Player> player)
        {
            _players[player->getId()] = std::move(player);
        }

        Player *getPlayer(int pid)
        {
            auto it = _players.find(pid);

            return (it != _players.end()) ? it->second.get() : nullptr;
        }

        const auto &players() const
        {
            return _players;
        }

        void drawPlayer(std::shared_ptr<TextureManager> textureManager)
        {
            for (const auto& player : _players) {
                player.second->draw(_color, textureManager);
            }
        }

        void updatePlayer(float dt)
        {
            for (const auto& player : _players) {
                player.second->update(dt);
            }
        }

        bool removePlayer(int pid)
        {
            if (_players.find(pid) == _players.end())
                return false;
            _players.erase(pid);
            return true;
        }

        void setEjection(int pid, Vector2 ejectorPos) const
        {
            for (const auto& player: _players) {
                if (player.second->getId() != pid && player.second->getPosF() == ejectorPos) {
                    player.second->setEjection(true);
                }
            }
        }

        bool movePlayer(int pid, int x, int y, animationDirection dir, int frequency)
        {
            if (_players.find(pid) == _players.end())
                return false;
            std::shared_ptr<Player> p = _players[pid];

            if (p->getEjection() == true) {
                p->setEjectionTarget({x, y});
                p->beginEjection(frequency);
                return true;
            }
            if (p->getDirection() != dir) {
                p->startTurn(dir);
                return true;
            }
            std::cout << "target x: " << x << ", y: " << y << ", actual : x: " << p->getPosF().x << ", y: " << p->getPosF().y << std::endl;
            if (x == p->getPosF().x + 24 || x == p->getPosF().x - 24 ||
                y == p->getPosF().y + 24 || y == p->getPosF().y - 24) {
                p->whereMove(frequency);
                return true;
            }
            p->setTeleportTarget({x, y});
            p->beginTeleport(frequency);
            return true;
        }

    private:
        std::string _id;
        Color _color;
        std::unordered_map<int, std::shared_ptr<Player>> _players;
};

#endif
