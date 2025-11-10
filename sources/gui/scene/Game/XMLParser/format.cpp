/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Pokemon
*/

#include "entities/Pokemon.hpp"
#include <iostream>
#include <sstream>

std::string XMLParser::createCacheKey(int pokemonId, animationType animType,
    animationDirection direction) const
{
    std::ostringstream oss;

    oss << pokemonId << "_" 
        << animationTypeToString(animType) << "_" 
        << directionToString(direction);
    return oss.str();
}

std::string XMLParser::formatPokemonId(int pokemonId) const
{
    return (pokemonId < 10) ? "000" + std::to_string(pokemonId) :
    (pokemonId < 100) ? "00" + std::to_string(pokemonId) :
    "0" + std::to_string(pokemonId);
}

int XMLParser::getAnimationIndex(animationType animType) const
{
    switch (animType) {
        case animationType::Walk:
        case animationType::WalkShadow:
            return 0;
        case animationType::Attack:
        case animationType::AttackShadow:
            return 1;
        case animationType::Double:
        case animationType::DoubleShadow:
            return 9;
        case animationType::Hurt:
        case animationType::HurtShadow:
            return 6;
        case animationType::Idle:
        case animationType::IdleShadow:
            return 7;
        case animationType::Rotate:
        case animationType::RotateShadow:
            return 12;
        default:
            return 7;
    }
}

std::string XMLParser::directionToString(animationDirection dir) const
{
    return std::to_string(static_cast<int>(dir));
}

std::string XMLParser::animationTypeToString(animationType anim) const
{
    return std::to_string(static_cast<int>(anim));
}

std::string XMLParser::getXMLPath(int pokemonId) const
{
    return "resources/pokemon_sprites/" + formatPokemonId(pokemonId) + "/AnimData.xml";
}

bool XMLParser::isAnimationShadow(animationType animType) const
{
    return animType == animationType::AttackShadow ||
    animType == animationType::DoubleShadow ||
    animType == animationType::HurtShadow ||
    animType == animationType::IdleShadow ||
    animType == animationType::RotateShadow ||
    animType == animationType::WalkShadow;
}

std::vector<animationFrame_t> XMLParser::parseAnimation(int pokemonId,
    animationType animType, animationDirection direction)
{
    std::string key = createCacheKey(pokemonId, animType, direction);
    std::vector<animationFrame_t> frames;
    auto it = _cachedAnimations.find(key);
    int animIndex = 0;
    std::string xmlPath;

    if (it != _cachedAnimations.end()) {
        return it->second;
    }
    xmlPath = getXMLPath(pokemonId);
    animIndex = getAnimationIndex(animType);
    try {
        frames = parseFromXMLFile(xmlPath, animIndex, direction);
    } catch (const XMLParser::XMLParserException &e) {
        std::cerr << e.what() << std::endl;
        throw XMLParser::XMLParserException("Parser Error.");
    }
    _cachedAnimations[key] = frames;
    return frames;
}
