/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** update
*/

#include "scenes/GameScene.hpp"
#include <memory>
#include <iostream>
#include <sstream>
#include <thread>

GameScene::GameScene(std::shared_ptr<TextureManager> textureManager,
    std::shared_ptr<TextManager> textManager, int screenWidth,
    int screenHeight, std::shared_ptr<SoundManager> soundManager,
    int port, const std::string &host, settings_t *settings)
: AScene(textureManager, textManager, false), camera({0.0f, 0.0f}, 0.0f, 6.0f),
    _hud(screenWidth, screenHeight, textManager, textureManager, getTheme()), _tiles(getTheme(), _textureManager),
    _pokemonManager(_textureManager), _gameModel(std::make_shared<GameModel>(_pokemonManager)),
    _soundManager(std::move(soundManager)), _settings(settings), _itemManager(_textureManager)
{
    unsigned char i = 0;

    srand(time(NULL));
    while (1) {
        std::string point;
        i = (i == 0) ? 1 : i % 4;
        try {
            _socket = std::make_unique<SocketClass>(host, port);
        } catch (const SocketClass::SocketException &e) {
            BeginDrawing();
            ClearBackground(BLACK);
            point = (i == 1) ? "." : (i == 2) ? ".." : (i == 3) ? "..." : ".";
            _textManager->drawText("Connecting to server" + point, {(screenW - 1000) / 2.0f, (screenH - 40) / 2.0f}, 100);
            EndDrawing();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            i++;
            continue;
        }
        break;
    }
    if (_settings->isMusic) {
        try {
            _themeMusic = _soundManager->getMusic("resources/music/" + getTheme().erase(0, 18) + ".mp3");
        } catch (const SoundManager::SoundManagerException &e) {
            _isResources = false;
        }
        if (_isResources) {
            PlayMusicStream(_themeMusic);
        }
    }
    _socket->monitorSockets();
    _socket->clearIBuffer();
    _socket->pushOutputBuffer("GRAPHIC\n");
    _socket->socketSend();
    setupInitialInformations();
}

void GameScene::init_values()
{
    std::cout << "INITIED VALUES FOR THE MAP" << std::endl;
    totalWidth = mapWidth + 2 + (2 * afterWallsThickness);
    totalHeight = mapHeight + 2 + (2 * afterWallsThickness);
    offsetX = -(totalWidth * tileSize) / 2.0f + tileSize / 2.0f;
    offsetY = -(totalHeight * tileSize) / 2.0f + tileSize / 2.0f;
    wallStartX = afterWallsThickness;
    wallStartY = afterWallsThickness;
    wallEndX = totalWidth - afterWallsThickness - 1;
    wallEndY = totalHeight - afterWallsThickness - 1;
}

void GameScene::setupInitialInformations()
{
    while (!isLoadedCompletely) {
        _socket->monitorSockets();
        parseInformations(_socket->getInputBuffer());
    }
}

void GameScene::parseInformations(std::string& buf)
{
    std::string line;
    std::istringstream ss(buf);

    line = buf.substr(0, buf.find_first_of("\n"));
    if (line.empty()) {
        return;
    }
    buf.erase(0, line.size() + 1);
    std::stringstream cmd(line);
    std::string cmdline;
    cmd >> cmdline;
    line.erase(0, cmdline.size());
    parseCommand(cmdline, line);
}

void GameScene::parseCommand(std::string cmd, std::string params)
{

    auto it = COMMAND_MAP.find(cmd);

    if (it != COMMAND_MAP.end()) {
        it->second(*this, params);
    }
}
