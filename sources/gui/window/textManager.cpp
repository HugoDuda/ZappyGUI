/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** textManager
*/

#include "managers/TextManager.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

TextManager::TextManager(const std::string &fontPath, [[maybe_unused]] int baseSize)
{
    font = LoadFontEx(fontPath.c_str(), 400, nullptr, 0);
    if (font.texture.id == 0) {
        throw TextManagerException("Can't load font : " + fontPath);
    }
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
}

TextManager::~TextManager()
{
    UnloadFont(font);
    clear();
}

void TextManager::loadLanguage(const std::string &langCode)
{
    std::string filepath = "resources/lang/" + langCode + ".txt";
    std::ifstream file(filepath);
    size_t pos = 0;
    std::string key;
    std::string value;

    if (!file.is_open()) {
        throw TextManagerException("Can't open language file : " + filepath);
    }
    translations.clear();
    for (std::string line; std::getline(file, line); ) {
        trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        pos = line.find('=');
        if (pos == std::string::npos) {
            continue;
        }
        key = line.substr(0, pos);
        value = line.substr(pos + 1);
        trim(key);
        trim(value);
        if (!key.empty() && !value.empty()) {
            translations[key] = value;
        }
    }
    file.close();
}

const std::string &TextManager::getText(const std::string &key) const
{
    auto it = translations.find(key);

    if (it != translations.end()) {
        return it->second;
    }
    return key;
}

void TextManager::clear()
{
    translations.clear();
}

void TextManager::drawCode(const std::string &key, Vector2 position,
    float fontSize, const std::string &optionnalText, Color tint) const
{
    const std::string &text = getText(key);
    Vector2 shadowPos = {position.x + fontSize / 10, position.y  + fontSize / 10};

    if (tint.r && tint.b && tint.g) {
        DrawTextEx(font, (text + optionnalText).c_str(), shadowPos, fontSize, SPACING, {64, 64, 64, 255});
    }
    DrawTextEx(font, (text + optionnalText).c_str(), position, fontSize, SPACING, tint);
}

void TextManager::drawText(const std::string &text, Vector2 position,
    float fontSize, Color tint) const
{
    Vector2 shadowPos = {position.x + fontSize / 10, position.y  + fontSize / 10};

    if (tint.r && tint.b && tint.g) {
        DrawTextEx(font, text.c_str(), shadowPos, fontSize, SPACING, {64, 64, 64, 255});
    }
    DrawTextEx(font, text.c_str(), position,   fontSize, SPACING, tint);
}

void TextManager::trim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }
    ));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }
    ).base(), s.end());
}
