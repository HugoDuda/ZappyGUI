/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** update
*/

#include "scenes/TitleScreenScene.hpp"

void TitleScreenScene::draw()
{
    drawBackground();
    drawBekipan();
    drawTitle();
    drawPressEnter();
    if (!letter.isTake)
        drawLetter();
    if (closeUpBekipan.active)
        drawCloseUpBekipan();
}

void TitleScreenScene::update(float dt)
{
    updateBackground(dt);
    updateBekipan(dt);
    updateCloseUpBekipan(dt);
    updateLetter(dt);
    updatePressEnter(dt);
    draw();
}
