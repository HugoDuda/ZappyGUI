/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** updatePlayer
*/

#include "network/Player.hpp"
#include "parser/XMLParser.hpp"
#include <iostream>

void Player::whereMove(int timer)
{
    if (_currentDir == animationDirection::North) {
        startMove({0, -24, BASE_TICKS.at(ActionType::Move)}, (float)timer);
    }
    if (_currentDir == animationDirection::East) {
        startMove({+24, 0, BASE_TICKS.at(ActionType::Move)}, (float)timer);
    }
    if (_currentDir == animationDirection::West) {
        startMove({-24, 0, BASE_TICKS.at(ActionType::Move)}, (float)timer);
    }
    if (_currentDir == animationDirection::South) {
        startMove({0, +24, BASE_TICKS.at(ActionType::Move)}, (float)timer);
    }
}

void Player::startMove(movePayload_t move, float serverFreq)
{
    _startPos = _tilePos;
    _endPos = {_tilePos.x + move.dx, _tilePos.y + move.dy};
    _duration = (float)move.serverTicks / (serverFreq + 1);
    _elapsed = 0.f;
    _busy = true;
    _currentDir = (move.dx > 0 ? animationDirection::East
    : move.dx < 0 ? animationDirection::West
    : move.dy > 0 ? animationDirection::South
    : animationDirection::North);
    _currentAnim = animationType::Walk;
    _skin->setDirection(_currentDir);
    _skin->setAnimation(_currentAnim);
}

void Player::startFork(float serverFreq)
{
    _duration = (float)BASE_TICKS.at(ActionType::Fork) / serverFreq;
    _elapsed = 0.f;
    _isForking = true;
    _currentAnim = animationType::Double;
    _skin->setAnimation(_currentAnim);
}

void Player::startIncantation(float serverFreq)
{
    _duration = (float)BASE_TICKS.at(ActionType::Incantation) / serverFreq + 1;
    _elapsed = 0.f;
    _isIncanting = true;
    _busy = true;
    _currentAnim = animationType::Rotate;
    _skin->setAnimation(_currentAnim);
}

void Player::endIncantation()
{
    _isIncanting = false;
}

void Player::beginEjection(float timer)
{
    _startPos = _tilePos;
    _endPos = _targetPos;
    _duration = (float)BASE_TICKS.at(ActionType::Move) / timer + 1;
    _elapsed = 0.f;
    _busy = true;
    _currentAnim = animationType::Hurt;
    _skin->setAnimation(_currentAnim);
}

void Player::beginTeleport(float timer)
{
    _startPos = _tilePos;
    _endPos = {_startPos.x, _tilePos.y - 600};
    _duration = (float)(BASE_TICKS.at(ActionType::Move) / (timer + 1)) / 2;
    _elapsed = 0.f;
    _busy = true;
    _currentAnim = animationType::Rotate;
    _isTeleport = true;
    _skin->setAnimation(_currentAnim);
}

void Player::endTeleport()
{
    _posF = { (float)_targetPos.x, (float)_targetPos.y - 600};
    _startPos = {(int)_posF.x, (int)_posF.y};
    _endPos = {_startPos.x, _startPos.y + 600};
    _elapsed = 0.f;
    _busy = true;
    _currentAnim = animationType::Rotate;
    _skin->setAnimation(_currentAnim);
}

void Player::startBroadcast(float serverFreq)
{
    _duration = (float)BASE_TICKS.at(ActionType::Broadcast) / serverFreq;
    _elapsed = 0.f;
    _isBroadcast = true;
}

void Player::broadcastEffect(std::shared_ptr<TextureManager> textureManager)
{
    float anim = 0.f;
    const float durationAnim = _duration / 5;
    
    if (_elapsed > durationAnim) {
        anim = 8.f;
    }
    if (_elapsed > durationAnim * 2) {
        anim = 16.f;
    }
    if (_elapsed > durationAnim * 3) {
        anim = 24.f;
    }
    if (_elapsed > durationAnim * 4) {
        anim = 32.f;
    }
    DrawTexturePro
    (
        textureManager->getTexture("resources/broadcastEffect.png"),
        {anim, 0.f, 7.f, 13.f},
        {_posF.x, _posF.y - getSkinHeight(), 7.f * 1.2f, 13.f * 1.2f},
        {0.f, 0.f},
        0.f,
        WHITE
    );
}

void Player::update(float dt)
{
    _skin->update(dt * 50);
    _elapsed += dt;
    if (!_busy) {
        _posF = {(float)_tilePos.x, (float)_tilePos.y};
        if (_isBroadcast) {
            if (_elapsed >= _duration) {
                _isBroadcast = false;
            }
        } else if (_isForking) {
            if (_elapsed >= _duration) {
                _isForking = false;
            }
        } else if (_currentAnim != animationType::Idle) {
            _currentAnim = animationType::Idle;
            _skin->setAnimation(_currentAnim);
        }
        return;
    }
    float time = std::min(_elapsed / _duration, 1.f);
    if (!_isIncanting) {
        _posF.x = _startPos.x + time * (_endPos.x - _startPos.x);
        _posF.y = _startPos.y + time * (_endPos.y - _startPos.y);
    }
    if (_elapsed >= _duration) {
        if (_isTeleport) {
            endTeleport();
            _isTeleport = false;
            return;
        } else if (_isIncanting) {
            _isIncanting = false;
            _busy = false;
            _skin->setAnimation(animationType::Idle);
            return;
        }
        _isEjected = false;
        _busy = false;
        _tilePos = _endPos;
        _skin->setAnimation(animationType::Idle);
    }
}

void Player::draw(Color shadowColor, std::shared_ptr<TextureManager> textureManager)
{
    if (_isBroadcast) {
        broadcastEffect(textureManager);
    }
    _skin->draw(_posF.x, _posF.y, shadowColor);
}
