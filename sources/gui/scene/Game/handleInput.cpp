/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** handleInput
*/

#include "scenes/GameScene.hpp"

SceneType GameScene::handleInput(float dt)
{
    _elapsedTimeFreq += dt;
    if (IsKeyDown(KEY_O) && _elapsedTimeFreq > 0.01f) {
        _tempTimer++;
        _elapsedTimeFreq = 0;
    }
    if (IsKeyDown(KEY_P) && _elapsedTimeFreq > 0.01f) {
        _tempTimer--;
        if (_tempTimer < 1) {
            _tempTimer = 1;
        }
        _elapsedTimeFreq = 0;
    }
    if (IsKeyReleased(KEY_O) || IsKeyReleased(KEY_P)) {
        _timer = _tempTimer;
        Commands::sst(*this, std::to_string(_timer));
    }
    if (IsKeyPressed(KEY_I)) {
        _toggleItem = !_toggleItem;
    }
    if (IsKeyPressed(KEY_G)) {
        _toggleGrid = !_toggleGrid;
    }
    if (IsKeyPressed(KEY_B)) {
        _hud.setDisplayInfoInterface(!_hud.getDisplayInfoInterface());
    }
    _hud.setDisplayMenuInterface(spectate);
    if (IsKeyPressed(KEY_LEFT) && !_gameModel->getlist().empty()) {
        if (spectate == true) {
            playerSpectateIndex = (playerSpectateIndex + 1) % _gameModel->getlist().size();
        }
        spectate = true;
    } else if (IsKeyPressed(KEY_RIGHT) && !_gameModel->getlist().empty()) {
        if (spectate == true) {
            playerSpectateIndex = (playerSpectateIndex + _gameModel->getlist().size() - 1) % _gameModel->getlist().size();
        }
        spectate = true;
    } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_A)) {
        spectate = false;
    }
    if (spectate == true && !_gameModel->getlist().empty()) {
        auto it = _gameModel->getlist().begin();
        std::advance(it, playerSpectateIndex);
        camera.setPosition(_gameModel->getPlayer(*it)->getPosF().x, _gameModel->getPlayer(*it)->getPosF().y);
    }
    camera.movement();
    camera.zoomControl();
    if (!GameEnded.empty()) {
        std::cout << "[ !! CONGRATS !! ] Game Ended, TEAM : " << GameEnded << " WON THE GAME !" << std::endl;
        return SceneType::EXIT;
    }
    return SceneType::NONE;
}
