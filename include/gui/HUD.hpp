/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** HUD
*/

#ifndef _HUD_HPP_
    #define _HUD_HPP_

    #include <memory>
    #include <string>
    #include <deque>
    #include <array>

    #include "Camera.hpp"
    #include "managers/TextureManager.hpp"

class HUD
{
    public:
        HUD(int screenWidth, int screenHeight,
            std::shared_ptr<TextManager> textManager, std::shared_ptr<TextureManager> textureManager, const std::string &theme)
        : _screenWidth(screenWidth), _screenHeight(screenHeight),
        _textManager(std::move(textManager)), _textureManager(std::move(textureManager)), _theme(theme)
        {}
        ~HUD() = default;
        void keybind(CameraScene camera);
        void setDisplayInfoInterface(bool info)
        {
            displayInfoInterface = info;
        }
        bool getDisplayInfoInterface()
        {
            return displayInfoInterface;
        }
        void setDisplayMenuInterface(bool menu)
        {
            displayMenuInterface = menu;
        }
        bool getDisplayMenuInterface()
        {
            return displayMenuInterface;
        }
        void addMessage(const std::string &msg)
        {
            if (msg.empty()) { 
                return;
            }
            _messages.push_back(msg);
            if (_messages.size() > maxMessages) {
                _messages.pop_front();
            }
        }
        void broadcast();
        void spectateMenu(const std::string &playerName,
            const std::string &level, const std::string &teamName, int pid, std::array<int, 7> inventory, bool isIncantation);
        std::string extractSecondField(const std::string &str)
        {
            size_t first = str.find(':');

            if (first == std::string::npos) {
                return "";
            }
            size_t second = str.find(':', first + 1);
            if (second == std::string::npos) {
                return "";
            }
            return str.substr(first + 1, second - first - 1);
        }
        void addBrodcast(int pid, std::string message)
        {
            _messages.push_back(std::to_string(pid) + " : " + extractSecondField(message));
            if (_messages.size() > maxMessages) {
                _messages.pop_front();
            }
        }
        void freq(int freq, float elapsedTimeFreq);
    private:
        std::string formatPokemonId(int pokemonId);
        int _screenWidth;
        int _screenHeight;
        std::shared_ptr<TextManager> _textManager;
        std::shared_ptr<TextureManager> _textureManager;
        bool displayInfoInterface = true;
        bool displayMenuInterface = false;
        std::deque<std::string> _messages;
        static const size_t maxMessages = 10;
        const std::string &_theme;
};

#endif
