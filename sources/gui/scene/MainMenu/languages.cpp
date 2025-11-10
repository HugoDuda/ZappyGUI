/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** languages
*/

#include "scenes/LanguageScreenScene.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <cerrno>

LanguageScreenScene::LanguageScreenScene
(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<TextManager> textManager)
: AScene(textureManager, textManager, true)
{
    languages = languagesParser();
    menuItemCount = languages.size();
    yStart = screenH * 0.165f;
    lineHeight = (screenH * 0.04f * menuItemCount);
    arrowIndex = 0;
}

std::string LanguageScreenScene::removeTxtExtension(const std::string &filename)
{
    constexpr const char *suffix = ".txt";
    constexpr size_t suffixLen = 4;

    return (filename.size() >= suffixLen &&
    filename.compare(filename.size() - suffixLen, suffixLen, suffix) == 0)
    ? filename.substr(0, filename.size() - suffixLen) : filename;
}

std::vector<std::string> LanguageScreenScene::languagesParser()
{
    std::vector<std::string> languages;
    std::string path = "resources/lang/";
    DIR *dir = opendir(path.c_str());
    struct dirent *entry;

    if (!dir) {
        languages.push_back("None");
        return languages;
    }
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }
        std::string fullPath = path + "/" + name;
        struct stat st;
        if (stat(fullPath.c_str(), &st) == 0) {
            if (S_ISREG(st.st_mode)) {
                languages.push_back(removeTxtExtension(name));
            }
        }
    }
    closedir(dir);
    return languages;
}

SceneType LanguageScreenScene::handleInput([[maybe_unused]] float dt)
{
    if (IsKeyReleased(KEY_DOWN)) {
        arrowIndex = (arrowIndex + 1) % menuItemCount;
    }
    if (IsKeyReleased(KEY_UP)) {
        arrowIndex = (arrowIndex - 1 + menuItemCount) % menuItemCount;
    }
    if (IsKeyReleased(KEY_ENTER)) {
        _textManager->loadLanguage(languages[arrowIndex]);
        return SceneType::MAINMENU;
    }
    if (IsKeyReleased(KEY_ESCAPE)) {
        return SceneType::MAINMENU;
    }
    return SceneType::NONE;
}

void LanguageScreenScene::update(float dt)
{
    (void)dt;
    draw();
}

void LanguageScreenScene::draw()
{
    Texture2D &arrow = _textureManager->getTexture("resources/menu/arrow.png");
    float arrowX = screenW * 0.037f;

    displayMenuInterface("LANGUAGES");
    for (int i = 0; i < menuItemCount; i++) {
        float y = yStart + i * lineHeight;
        if (i == arrowIndex) {
            DrawTextureEx(arrow, {arrowX, y}, 0.f, 1.45f, WHITE);
        }
        _textManager->drawText(languages[i],
        {screenW * 0.038f + arrow.width * 2.f, y}, 70.f);
    }
}
