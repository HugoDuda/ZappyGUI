/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** keybind
*/

#include "HUD.hpp"
#include <iostream>

void HUD::keybind(CameraScene camera)
{
    _textManager->drawText("WASD: Move, UP or DOWN: Zoom, B: Hide or display broadcast interface, I: Hide or display items, P: Up server frequence, O: Down server frequence.", {10, 0}, 25, BLACK);
    _textManager->drawText(TextFormat("Position: (%.1f, %.1f)", camera.getPosition().x, camera.getPosition().y), {10, 30}, 25, BLACK);
    _textManager->drawText(TextFormat("Zoom: %.2f", camera.getZoom()), (Vector2){10, 60}, 25, BLACK);
}
