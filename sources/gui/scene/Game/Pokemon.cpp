/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Pokemon
*/

#include "entities/Pokemon.hpp"
#include <string.h>
#include <iostream>

Pokemon::Pokemon(int pokemonId, std::shared_ptr<TextureManager> textureManager)
: _id(pokemonId),_textureManager(std::move(textureManager))
{
    for (animationDirection dir : {
        animationDirection::North,
        animationDirection::East,
        animationDirection::South,
        animationDirection::West,}) {
        auto &animMap = _animations[dir];
        for (animationType anim : {
            animationType::Idle,
            animationType::Walk,
            animationType::Attack,
            animationType::Hurt,
            animationType::Rotate,
            animationType::Double}) {
            try {
                animMap[anim] = XMLParser::getInstance().parseAnimation(_id, anim, dir);
            } catch (const XMLParser::XMLParserException &e) {
                animMap[anim].push_back({{
                    static_cast<float>(-1),
                    static_cast<float>(-1),
                    static_cast<float>(-1),
                    static_cast<float>(-1)
                }, 0.f});
            }
        }
    }
}

Texture2D Pokemon::makeShadowTexture(const Texture2D &src, Color color, Rectangle rect)
{
    Image img = LoadImageFromTexture(src);
    Color *pixels = LoadImageColors(img);
    int startX = ((int)rect.x < 0) ? 0 : (int)rect.x;
    int startY = ((int)rect.y < 0) ? 0 : (int)rect.y;
    int endX = ((int)(rect.x + rect.width) > img.width) ? img.width : (int)(rect.x + rect.width);
    int endY = ((int)(rect.y + rect.height) > img.height) ? img.height : (int)(rect.y + rect.height);
    Texture tmp;

    for (int y = startY; y < endY; ++y) {
        for (int x = startX; x < endX; ++x) {
            int i = y * img.width + x;
            if (pixels[i].a > 0) {
                pixels[i].r = color.r;
                pixels[i].g = color.g;
                pixels[i].b = color.b;
            }
        }
    }
    memcpy(img.data, pixels, img.width * img.height * sizeof(Color));
    tmp = LoadTextureFromImage(img);
    UnloadImageColors(pixels);
    UnloadImage(img);
    return tmp;
}

void Pokemon::draw(float x, float y, Color shadowColor)
{
    const auto &frames = _animations.at(_currentDir).at(_currentAnim);
    float cum = 0.f;
    size_t idx = 0;
    float t = 0;
    Rectangle src = {0, 0, 0, 0};
    struct stat st{};

    if (frames.empty()) {
        return;
    }
    t = fmod(_timeAccumulator, totalAnimationTime(frames));
    for (; idx < frames.size(); ++idx) {
        cum += frames[idx].duration;
        if (t < cum) {
            break;
        }
    }
    if (idx >= frames.size()) {
        idx = frames.size() - 1;
    }
    src = frames[idx].sourceRect;
    textureHeight = src.height;
    if (src.height != -1 && src.width != -1 && src.x != -1 && src.y != -1) {
        if (stat(("resources/pokemon_sprites/" + formatPokemonId(_id) + "/" +
        animationTypeToFilename(_currentAnim) + ".png").c_str(), &st) != 0) {
            if (animationTypeToFilename(_currentAnim) == "Idle-Anim") {
                _currentAnim = animationType::Walk;
            } else if (animationTypeToFilename(_currentAnim) == "Walk-Anim") {
                _currentAnim = animationType::Idle;
            }
        }
        auto key = std::make_tuple(_currentAnim, _currentDir, colorToArray(shadowColor), rectKey_t(src));
        auto it = shadowCache.find(key);
        if (it == shadowCache.end()) {
            shadowCache[key] = makeShadowTexture(
            _textureManager->getTexture("resources/pokemon_sprites/"
            + formatPokemonId(_id) + "/" + shadowToFilename(_currentAnim) + ".png"), shadowColor, src);
            it = shadowCache.find(key);
        }
        DrawTextureRec(it->second, src, {x - src.width/2.f, y - src.height/2.f}, WHITE);
        DrawTextureRec(_textureManager->getTexture("resources/pokemon_sprites/" +
        formatPokemonId(_id) + "/" + animationTypeToFilename(_currentAnim) + ".png"),
        src, {x - src.width/2.f, y - src.height/2.f}, WHITE);
    } else {
        DrawTextureRec(_textureManager->getTexture("none"),
        {24, 24, 24, 24}, {x - 12, y - 12}, WHITE);
    }
}

std::unique_ptr<Pokemon> Pokemon::clone() const
{
    auto p = std::make_unique<Pokemon>(_id, _textureManager);

    p->_animations = _animations;
    p->_timeAccumulator = _timeAccumulator;
    p->_currentAnim = _currentAnim;
    p->_currentDir = _currentDir;
    return p;
}

const std::string Pokemon::animationTypeToFilename(animationType anim) const
{
    if (anim == animationType::Idle) {
        return "Idle-Anim";
    }
    if (anim == animationType::Walk) {
        return "Walk-Anim";
    }
    if (anim == animationType::Attack) {
        return "Attack-Anim";
    }            
    if (anim == animationType::Hurt) {
        return "Hurt-Anim";
    }
    if (anim == animationType::Rotate) {
        return "Rotate-Anim";
    }
    if (anim == animationType::Double) {
        return "Double-Anim";
    }
    return "Idle-Anim";
}

const std::string Pokemon::shadowToFilename(animationType anim) const
{
    if (anim == animationType::Idle) {
        return "Idle-Shadow";
    }
    if (anim == animationType::Walk) {
        return "Walk-Shadow";
    }
    if (anim == animationType::Attack) {
        return "Attack-Shadow";
    }            
    if (anim == animationType::Hurt) {
        return "Hurt-Shadow";
    }
    if (anim == animationType::Rotate) {
        return "Rotate-Shadow";
    }
    if (anim == animationType::Double) {
        return "Double-Shadow";
    }
    return "Idle-Shadow";
}
