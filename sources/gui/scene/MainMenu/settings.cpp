/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Settings
*/

#include "scenes/SceneManager.hpp"

SettingsScreenScene::SettingsScreenScene
(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<TextManager> textManager, settings_t *settings)
: AScene(textureManager, textManager, true), _settings(settings)
{
    menuItemCount = 4;
    yStart = screenH * 0.165f;
    lineHeight = (screenH * 0.30f) / static_cast<float>(menuItemCount);
    arrowIndex = 0;
    settingsOptions = {
        "SETTING_MUSIC",
        "SETTING_SOUND",
        "SETTING_ANIMATION",
        "SETTING_APPLY_AND_LEAVE",
    };
    settingsStat = {
        "SETTING_DISABLED",
        "SETTING_ENABLED"
    };
}

SceneType SettingsScreenScene::handleInput([[maybe_unused]] float dt)
{
    if (arrowIndex == 3 && IsKeyReleased(KEY_ENTER)) {
        return SceneType::MAINMENU;
    }
    if (arrowIndex < 3 && IsKeyReleased(KEY_ENTER)) {
        if (arrowIndex == 0) {
            _settings->isMusic = !_settings->isMusic;
        }
        if (arrowIndex == 1) {
            _settings->isSound = !_settings->isSound;
        }
        if (arrowIndex == 2) {
            _settings->isAnimation = !_settings->isAnimation;
        }
    }
    if (IsKeyReleased(KEY_DOWN)) {
        arrowIndex = (arrowIndex + 1) % menuItemCount;
    }
    if (IsKeyReleased(KEY_UP)) {
        arrowIndex = (arrowIndex - 1 + menuItemCount) % menuItemCount;
    }
    if (IsKeyReleased(KEY_ESCAPE)) {
        return SceneType::MAINMENU;
    }
    return SceneType::NONE;
}

void SettingsScreenScene::update(float dt)
{
    (void)dt;
    draw();
}

void SettingsScreenScene::draw()
{
    float arrowX = screenW * 0.037f;
    Texture2D &arrow = _textureManager->getTexture("resources/menu/arrow.png");

    displayMenuInterface("SETTINGS");
    for (int i = 0; i < menuItemCount; ++i) {
        float y = yStart + i * lineHeight;
        if (i == arrowIndex) {
            DrawTextureEx(arrow, {arrowX, y}, 0.f, 1.45f, WHITE);
        }
        _textManager->drawCode(settingsOptions[i],
        {screenW * 0.038f + arrow.width * 2.f, y}, 70.f);
        if (i == 0) {
            _textManager->drawCode(settingsStat[_settings->isMusic],
            {screenW * 0.60f + arrow.width * 2.f, y}, 70.f);
        }
        if (i == 1) {
            _textManager->drawCode(settingsStat[_settings->isSound],
            {screenW * 0.60f + arrow.width * 2.f, y}, 70.f);
        }
        if (i == 2) {
            _textManager->drawCode(settingsStat[_settings->isAnimation],
            {screenW * 0.60f + arrow.width * 2.f, y}, 70.f);
        }
    }
}
