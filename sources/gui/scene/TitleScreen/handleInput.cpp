/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** handleInput
*/

#include "scenes/TitleScreenScene.hpp"

SceneType TitleScreenScene::handleInput(float dt)
{
    (void)dt;
    if (IsKeyReleased(KEY_ENTER)) {
        return SceneType::MAINMENU;
    }
    return SceneType::NONE;
}
