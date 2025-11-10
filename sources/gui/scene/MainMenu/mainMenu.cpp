/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** MainMenuScene
*/

#include "scenes/MenuScene.hpp"

std::string AScene::themeFile = "resources/dungeon/Hidden Land";
MainMenuScene::MainMenuScene(std::shared_ptr<TextureManager> textureManager, 
    std::shared_ptr<TextManager> textManager)
: AScene(textureManager, textManager, false)
{
    menuItemCount = 6;
    yStart = screenH * 0.07f;
    lineHeight = (screenH * 0.47f) / static_cast<float>(menuItemCount);
    arrowIndex = 0;
    menuOptions = {
        "MENU_PLAY",
        "MENU_SETTINGS",
        "MENU_THEME",
        "MENU_LANGUAGE",
        "MENU_POKEDEX",
        "MENU_EXIT"
    };
    menuDescOptions = {
        "MENU_PLAY_DESC",
        "MENU_SETTINGS_DESC",
        "MENU_THEME_DESC",
        "MENU_LANGUAGE_DESC",
        "MENU_POKEDEX_DESC",
        "MENU_EXIT_DESC"
    };
}

SceneType MainMenuScene::handleInput([[maybe_unused]] float dt)
{
    if (IsKeyReleased(KEY_DOWN)) {
        arrowIndex = (arrowIndex + 1) % menuItemCount;
    }
    if (IsKeyReleased(KEY_UP)) {
        arrowIndex = (arrowIndex - 1 + menuItemCount) % menuItemCount;
    }
    if (IsKeyReleased(KEY_ENTER)) {
        if (arrowIndex == 0) {
            return SceneType::GAMEPLAY;
        }
        if (arrowIndex == 1) {
            return SceneType::MENU_SETTINGS;
        }
        if (arrowIndex == 2) {
            return SceneType::MENU_THEME;
        }
        if (arrowIndex == 3) {
            return SceneType::MENU_LANGUAGE;
        }
        if (arrowIndex == 5) {
            return SceneType::EXIT;
        }
    }
    return SceneType::NONE;
}

void MainMenuScene::update(float dt)
{
    (void)dt;
    draw();
}

void MainMenuScene::draw()
{
    Texture2D &background = _textureManager->getTexture(_path);
    Texture2D &menu = _textureManager->getTexture("resources/menu/menu.png");
    Texture2D &arrow = _textureManager->getTexture("resources/menu/arrow.png");
    float scaleX = (float)screenW / background.width;
    float scaleMenuY = (float)screenH / menu.height;
    float menuOffset = 0;
    float arrowX = screenW * 0.037f + menuOffset;

    DrawTextureEx(background, { 0.f, 0.f }, 0.f, scaleX, WHITE);
    DrawTextureEx(menu, {menuOffset, 0.f }, 0.f, scaleMenuY, WHITE);
    for (int i = 0; i < menuItemCount; ++i) {
        float y = yStart + i * lineHeight;
        if (i == arrowIndex) {
            DrawTextureEx(arrow, {arrowX, y}, 0.f, 1.45f, WHITE);
        }
        _textManager->drawCode(menuOptions[i], {menuOffset + screenW * 0.038f + arrow.width * 2.f, y}, 70.f);
    }
    _textManager->drawCode(menuDescOptions[arrowIndex], {menuOffset + screenW * 0.04f, screenH * 0.78f}, 70.f);
}
