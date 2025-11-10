/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Player
*/

#ifndef _PLAYER_HPP_
    #define _PLAYER_HPP_

    #include <iostream>

    #include "entities/Pokemon.hpp"
    #include "parser/XMLParser.hpp" 

    #include <array>

typedef struct {
    int x;
    int y;
} position_t;

enum class ActionType
{
    Move,
    Turn,
    Look,
    Eject,
    Inventory,
    Broadcast,
    Fork,
    Incantation
};

static const std::unordered_map<ActionType, int> BASE_TICKS = {
    {ActionType::Move,          7},
    {ActionType::Turn,          7},
    {ActionType::Eject,         7},
    {ActionType::Broadcast,     7},
    {ActionType::Fork,         42},
    {ActionType::Incantation, 300},
};

typedef struct {
    int dx;
    int dy;
    int serverTicks;
} movePayload_t;

class Player
{
    public:
        Player(int id, std::string teamId, position_t startTile,
        std::unique_ptr<Pokemon> skin, animationDirection dir)
        : _id(id), _tname(teamId), _currentDir(dir),
        _tilePos(startTile), _posF{(float)startTile.x,
        (float)startTile.y}, _skin(std::move(skin))
        {
            _skin->setAnimation(animationType::Idle);
            _skin->setDirection(dir);
        }
        ~Player() = default;
        int getId() const
        {
            return _id;
        }
        const std::string& getTeamId() const
        {
            return _tname;
        }
        position_t getPosition() const
        {
            return _position;
        }
        animationDirection getDirection() const
        {
            return _currentDir;
        }
        void setPosition(position_t position)
        {
            _position = position;
        }
        void setDirection(animationDirection direction)
        {
            _currentDir = direction;
        }
        bool isBusy()
        {
            return _busy;
        }
        void update(float dt);
        void draw(Color shadowColor, std::shared_ptr<TextureManager> textureManager);
        void startMove(movePayload_t move, float serverFreq);
        void whereMove(int timer);
        void startTurn(animationDirection newDir)
        {
            _currentDir = newDir;
            _skin->setDirection(_currentDir);
        }
        Vector2 getPosF() const
        {
            return _posF;
        }
        void setTeleportTarget(position_t target) { _targetPos = target; };
        void beginTeleport(float timer);
        void endTeleport();
        void setPlayerLvl(unsigned char lvl) { _level = lvl; };
        unsigned char getPlayerlvl()
        {
            return _level;
        }
        std::string getTeamName()
        {
            return _tname;
        }
        void setForking(bool isForking)
        {
            _isForking = isForking;
        }
        void beginEjection(float timer);
        void setEjectionTarget(position_t target) { _targetPos = target; };
        bool getEjection() { return _isEjected; };
        void setEjection(bool isEjected)
        {
            _isEjected = isEjected;
        }
        int getPokemonId()
        {
            return _skin->getId();
        }
        float getSkinHeight()
        {
            return _skin->getTextureHeight();
        }
        void setInventory(int food, int line, int derau, int sib, int mend, int phir, int thyst)
        {
            inventory[0] = food;
            inventory[1] = line;
            inventory[2] = derau;
            inventory[3] = sib;
            inventory[4] = mend;
            inventory[5] = phir;
            inventory[6] = thyst;
        }
        std::array<int, 7> getInventory()
        {
            return inventory;
        }
        void startFork(float serverFreq);
        void startIncantation(float serverFreq);
        void endIncantation();
        void broadcastEffect(std::shared_ptr<TextureManager> textureManager);
        void startBroadcast(float serverFreq);
        bool getIncantation()
        {
            return _isIncanting;
        }

    private:
        int _id;
        std::string _tname; 
        position_t _position;
        bool _busy = false;
        float _elapsed = 0.f;
        float _duration = 0.f;
        position_t _startPos{};
        position_t _endPos{};
        animationType _currentAnim = animationType::Idle;
        animationDirection _currentDir  = animationDirection::South;
        position_t _tilePos;
        Vector2 _posF;
        std::unique_ptr<Pokemon> _skin;
        float _actionElapsed = 0.f;
        bool _isTeleport = false;
        position_t _targetPos {};
        unsigned char _level = 1;
        bool _isForking = false;
        bool _isIncanting = false;
        bool _isEjected = false;
        bool _isBroadcast = false;
        std::array<int, 7> inventory{};
};

#endif
