/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** update
*/

#include "scenes/GameScene.hpp"

void GameScene::draw()
{
    displayMap();
    if (_toggleItem) {
        _itemManager.drawAll();
    }
    _gameModel->drawAll(_textureManager);
}

void GameScene::HUDHandling()
{
    _hud.keybind(camera);
    _hud.broadcast();
    if (spectate && !_gameModel->getlist().empty()) {
        auto it = _gameModel->getlist().begin();
        if (playerSpectateIndex > static_cast<int>(_gameModel->getlist().size() - 1)) {
            playerSpectateIndex = static_cast<int>(_gameModel->getlist().size() - 1);
        }
        if (playerSpectateIndex < 0) {
            playerSpectateIndex = 0;
        }
        std::advance(it, playerSpectateIndex);
        _hud.spectateMenu(std::to_string(_gameModel->getPlayer(*it)->getId()),
        std::to_string(_gameModel->getPlayer(*it)->getPlayerlvl()),
        _gameModel->getPlayer(*it)->getTeamName(), _gameModel->getPlayer(*it)->getPokemonId(),
        _gameModel->getPlayer(*it)->getInventory(), _gameModel->getPlayer(*it)->getIncantation());
    }
    _hud.freq(_tempTimer, _elapsedTimeFreq);
}

void GameScene::update(float dt)
{
    try {
        _socket->monitorSockets();
    } catch (const SocketClass::SocketException& e) {
        throw ASceneException("Server Disconnected.");
    }
    parseInformations(_socket->getInputBuffer());
    if (!isLoadedCompletely) {
        return;
    }
    if (_settings->isMusic) {
        UpdateMusicStream(_themeMusic);
    }
    _gameModel->updateAll(dt);
    camera.begin();
    draw();
    camera.end();
    HUDHandling();
}
