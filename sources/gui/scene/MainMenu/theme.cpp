/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** theme
*/

#include "scenes/ThemeScreenScene.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <cerrno>

ThemeScreenScene::ThemeScreenScene
(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<TextManager> textManager)
: AScene(textureManager, textManager, true)
{
    themeOptions = themeParser();
    for (auto &themeOption : themeOptions) {
        dungeonsPreview.push_back(_textureManager->getTexture("resources/dungeon/preview/" + themeOption + ".png"));
    }
    menuItemCount = themeOptions.size();
    yStart = screenH * 0.165f;
    lineHeight = (screenH * 0.08f * menuItemCount) / static_cast<float>(menuItemCount);
    arrowIndex = 0;
}

std::string ThemeScreenScene::removePngExtension(const std::string &filename)
{
    constexpr const char* suffix = ".png";
    constexpr size_t suffixLen = 4;

    return (filename.size() >= suffixLen &&
    filename.compare(filename.size() - suffixLen, suffixLen, suffix) == 0)
    ? filename.substr(0, filename.size() - suffixLen) : filename;
}

std::vector<std::string> ThemeScreenScene::themeParser()
{
    std::vector<std::string> files;
    std::string path = "resources/dungeon/preview";
    DIR *dir = opendir(path.c_str());
    struct dirent *entry;

    if (!dir) {
        files.push_back(removePngExtension("None"));
        return files;
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
                files.push_back(removePngExtension(name));
            }
        }
    }
    closedir(dir);
    return files;
}

SceneType ThemeScreenScene::handleInput([[maybe_unused]] float dt)
{
    if (IsKeyReleased(KEY_DOWN)) {
        arrowIndex = (arrowIndex + 1) % menuItemCount;
    }
    if (IsKeyReleased(KEY_UP)) {
        arrowIndex = (arrowIndex - 1 + menuItemCount) % menuItemCount;
    }
    if (IsKeyReleased(KEY_ENTER)) {
        setTheme(themeOptions[arrowIndex]);
        return SceneType::MAINMENU;
    }
    if (IsKeyReleased(KEY_ESCAPE)) {
        return SceneType::MAINMENU;
    }
    return SceneType::NONE;
}

void ThemeScreenScene::update(float dt)
{
    (void)dt;
    draw();
}

void ThemeScreenScene::draw()
{
    float arrowX = screenW * 0.037f;
    Texture2D &arrow = _textureManager->getTexture("resources/menu/arrow.png");

    displayMenuInterface("THEME");
    for (int i = 0; i < menuItemCount; ++i) {
        float y = yStart + i * lineHeight;
        if (i == arrowIndex) {
            DrawTextureEx(arrow, {arrowX, y}, 0.f, 1.45f, WHITE);
        }
        _textManager->drawCode(themeOptions[i],
        {screenW * 0.038f + arrow.width * 2.f, y}, 70.f);
    }
    DrawTextureEx(dungeonsPreview[arrowIndex], {screenW * 0.54f, screenH * 0.2f}, 0.f, 6, WHITE);
}
