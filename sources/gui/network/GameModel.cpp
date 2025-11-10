#include "network/GameModel.hpp"
#include <memory>

Team &GameModel::createTeam(std::string id, Color color)
{
    auto team = std::make_unique<Team>(id, color);
    Team &ref = *team;

    _teams[id] = std::move(team);
    return ref;
}

void GameModel::createPlayer(int pid, std::string tname, position_t pos, int pokeId, animationDirection dir)
{
    auto &team = _teams.at(tname);
    auto skin = _pokemonManager.createPokemon(pokeId);
    auto p = std::make_shared<Player>(pid, tname, pos, std::move(skin), dir);
    
    pidList.push_back(pid);
    team->addPlayer(std::move(p));
}

bool GameModel::removePlayer(int pid)
{
    bool removed = false;

    for (const auto& team : _teams) {
        if (team.second->removePlayer(pid)) {
            pidList.remove(pid);
            removed = true;
        }
    }
    return removed;
}

const std::unordered_map<std::string, std::unique_ptr<Team>> &GameModel::teams() const
{
    return _teams;
}

void GameModel::drawAll(std::shared_ptr<TextureManager> textureManager) const
{
    for (const auto& team : _teams) {
        team.second->drawPlayer(textureManager);
    }
}

void GameModel::updateAll(float dt)
{
    for (const auto& team : _teams) {
        team.second->updatePlayer(dt);
    }
}

bool GameModel::movePlayer(int pid, int x, int y, animationDirection dir, int frequency)
{
    bool moved = false;

    for (const auto& team : _teams) {
        if (team.second->movePlayer(pid, x, y, dir, frequency))
            moved = true;
    }
    return moved;
}

std::shared_ptr<Player> GameModel::getPlayer(int pid)
{
    for (const auto& team : _teams) {
        if (team.second->players().find(pid) != team.second->players().end()) {
            auto map = team.second->players();
            return map[pid];
        }
    }
    return nullptr;
}

void GameModel::startIncantations(std::vector<int> pids, int timer)
{
    for (size_t i = 0; i < pids.size(); i++) {
        getPlayer(pids[i])->startIncantation(timer);
    }
}

void GameModel::endIncantations(std::vector<int> pids)
{
    for (const auto &pid : pids) {
        getPlayer(pid)->endIncantation();
    }
}

void GameModel::setEjection(int pid)
{
    Vector2 playerPos = getPlayer(pid)->getPosF();

    for (const auto& team: _teams) {
        team.second->setEjection(pid, playerPos);
    }
}
