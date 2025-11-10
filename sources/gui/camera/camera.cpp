/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Camera
*/

#include "Camera.hpp"

CameraScene::CameraScene(Vector2 position, float rotation, float zoom)
{
    camera = {};
    camera.target = position;
    camera.offset = {960.0f, 540.0f};
    camera.rotation = rotation;
    camera.zoom = zoom;
}

void CameraScene::rotation()
{
    if (IsKeyDown(KEY_LEFT)) {
        camera.rotation -= rotationSpeed * GetFrameTime();
    }
    if (IsKeyDown(KEY_RIGHT)) {
        camera.rotation += rotationSpeed * GetFrameTime();
    }
    if (camera.rotation >= 360.0f) {
        camera.rotation -= 360.0f;
    }
    if (camera.rotation < 0.0f) {
        camera.rotation += 360.0f;
    }
}

void CameraScene::movement()
{
    Vector2 move = {0, 0};
    float rotRad = camera.rotation * DEG2RAD;
    Vector2 forward = {sin(rotRad), -cos(rotRad)};
    Vector2 right = {cos(rotRad), sin(rotRad)};

    if (IsKeyDown(KEY_W)) {
        move = Vector2Add(move, forward);
    }
    if (IsKeyDown(KEY_S)) {
        move = Vector2Subtract(move, forward);
    }
    if (IsKeyDown(KEY_D)) {
        move = Vector2Add(move, right);
    }
    if (IsKeyDown(KEY_A)) {
        move = Vector2Subtract(move, right);
    }
    if (Vector2Length(move) > 0.0f) {
        move = Vector2Normalize(move);
        move = Vector2Scale(move, moveSpeed * GetFrameTime() / camera.zoom);
        camera.target = Vector2Add(camera.target, move);
    }
}

void CameraScene::zoomControl()
{
    if (IsKeyDown(KEY_UP)) {
        camera.zoom += zoomSpeed * GetFrameTime();
        if (camera.zoom > maxZoom) {
            camera.zoom = maxZoom;
        }
    }
    
    if (IsKeyDown(KEY_DOWN)) {
        camera.zoom -= zoomSpeed * GetFrameTime();
        if (camera.zoom < minZoom) {
            camera.zoom = minZoom;
        }
    }
}

void CameraScene::begin()
{
    BeginMode2D(camera);
}

void CameraScene::end()
{
    EndMode2D();
}
