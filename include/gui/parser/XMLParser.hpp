/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Window
*/

#ifndef _XMLPARSER_HPP_
    #define _XMLPARSER_HPP_

    #include "raylib.h"
    #include <unordered_map>
    #include <string>
    #include <vector>
    #include <fstream>
    #include <exception>

typedef struct {
    Rectangle sourceRect;
    float duration;
} animationFrame_t;

enum class animationType {
    Attack,
    AttackShadow,
    Double,
    DoubleShadow,
    Hurt,
    HurtShadow,
    Idle,
    IdleShadow,
    Rotate,
    RotateShadow,
    Walk,
    WalkShadow
};

enum class animationDirection : int {
    South = 0,
    East = 2,
    North = 4,
    West = 6
};

class XMLParser
{
    public:
        static XMLParser &getInstance()
        {
            static XMLParser instance;

            return instance;
        }

        class XMLParserException : public std::exception
        {
            public:
                explicit XMLParserException(const std::string &message)
                    : _message("[XMLPARSER] " + message)
                {}
                ~XMLParserException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        std::vector<animationFrame_t> parseAnimation(int pokemonId, animationType animType,
            animationDirection direction);
        XMLParser(const XMLParser &) = delete;
        XMLParser &operator=(const XMLParser &) = delete;

    private:
        XMLParser() = default;
        ~XMLParser() = default;
        struct parsingContext_t {
            std::vector<animationFrame_t> frames;
            bool foundTargetAnim = false;
            int currentIndex = -1;
            int frameWidth = 0;
            int frameHeight = 0;
            bool hasFrameWidth = false;
            bool hasFrameHeight = false;
            animationDirection direction = animationDirection::South;
        };
        std::unordered_map<std::string, std::vector<animationFrame_t>> _cachedAnimations;
        std::string createCacheKey(int pokemonId, animationType animType,
            animationDirection direction) const;
        std::string formatPokemonId(int pokemonId) const;
        std::string animationTypeToString(animationType animType) const;
        std::string directionToString(animationDirection dir) const;
        int getAnimationIndex(animationType animType) const;
        std::string getXMLPath(int pokemonId) const;
        std::vector<animationFrame_t> parseFromXMLFile(const std::string &xmlPath,
            int animIndex, animationDirection direction);
        bool isAnimationShadow(animationType animType) const;
        void findAnimationByIndex(std::string &line, const std::string &xmlPath,
            int animIndex, parsingContext_t &ctx);
        void parseFrameWidth(std::string &line, int animIndex, parsingContext_t &ctx);
        void parseFrameHeight(std::string &line, int animIndex, parsingContext_t &ctx);
        void parseDuration(std::string &line, int animIndex, parsingContext_t &ctx);
};

#endif
