/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Camera2D
*/

#ifndef _CAMERA_HPP_
    #define _CAMERA_HPP_

    #include "raylib.h"
    #include "raymath.h"

class CameraScene
{
    public:
        CameraScene(Vector2 position, float rotation, float zoom);
        ~CameraScene() = default;
        void begin();
        void end();
        void setPosition(const float &newX, const float &newY)
        {
            camera.target.x = newX;
            camera.target.y = newY;
        }
        Vector2 getPosition()
        {
            return camera.target;
        }
        void movement();
        void rotation();
        void zoomControl();
        float getZoom() const
        {
            return camera.zoom;
        }
        float getRotation() const
        {
            return camera.rotation;
        }

    private:
        const float moveSpeed = 600.0f;
        const float rotationSpeed = 90.0f;
        const float zoomSpeed = 3.0f;
        const float minZoom = 2.2f;
        const float maxZoom = 7.f;
        Camera2D camera;
};

#endif
