/*
** EPITECH PROJECT, 2025
** *
** File description:
** TitleScreenScene
*/

#ifndef _TITLE_SCREEN_SCENE_HPP_
    #define _TITLE_SCREEN_SCENE_HPP_

    #include "scenes/AScene.hpp"

class TitleScreenScene : public AScene
{
    public:
        TitleScreenScene(std::shared_ptr<TextureManager> textureManager);
        ~TitleScreenScene() = default;
        void update(float dt) override;
        SceneType handleInput(float dt) override;
        SceneType getType() const override
        {
            return SceneType::TITLESCREEN;
        }
        void onExit() override
        {
            _textureManager->resetPlaceholder();
        }
    private:
        void draw() override;
        void updateBackground(float dt);
        void drawBackground();
        void drawTitle();
        void drawPressEnter();
        void updatePressEnter(float dt);
        void drawLetter();
        void updateLetter(float dt);
        void drawBekipan();
        void updateBekipan(float dt);
        void drawCloseUpBekipan();
        void updateCloseUpBekipan(float dt);
        typedef struct {
            float scale = 1;
        } title_t;
        typedef struct {
            float scroll = 0.f;
            float scrollSpeed = 150.f;
        } background_t;
        typedef struct {
            float scale = 0.35;
            float posX = 0;
            float posY = 0;
            float blinkTimer = 0.f;
            const float blinkInterval = 1.5f;
        } pressEnter_t;
        typedef struct {
            float scale = 1.7;
            float y = -200.f;
            float speed = 120.f;
            float baseX = 0.f;
            float oscillationAmp = 70.f;
            float oscillationFreq = 0.7f;
            float time = 0.f;
            float rotationAmp = 5.f;
            bool isTake = false;
        } letter_t;
        typedef struct {
            float x = 0.f;
            float y = 0.f;
            float speed = 280.f;
            float animTimer = 0.f;
            int frame = 0;
            const int frameCount = 6;
            const int frameWidths[6] = {32, 32, 32, 32, 32, 32};
            const int frameDurations[6] = {10, 4, 8, 10, 4, 8};
            int currentDuration = 0;
            int frameWidth = 32;
            int frameHeight = 40;
            float scale = 4.5f;
        } bekipan_t;
        typedef struct {
            bool active = false;
            bool done = false;
            float timer = 0.f;
            float duration = 1.0f;
            float x = 0.f;
            float y = 0.f;
            float startScale = 3.0f;
            float endScale = 20.0f;
            Vector2 currentPos = {0.f, 0.f};
            float currentScale = 3.0f;
            Vector2 start;
            Vector2 end;
        } closeUpBekipan_t;
        title_t title;
        background_t background;
        pressEnter_t pressEnter;
        letter_t letter;
        bekipan_t bekipan;
        closeUpBekipan_t closeUpBekipan;
};

#endif
