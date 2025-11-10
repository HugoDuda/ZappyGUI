/*
** EPITECH PROJECT, 2025
** *
** File description:
** MenuScene
*/

#ifndef _MENU_SCENE_HPP_
    #define _MENU_SCENE_HPP_

    #include <vector>

    #include "scenes/AScene.hpp"

class MainMenuScene : public AScene
{
    public:
        MainMenuScene(std::shared_ptr<TextureManager> textureManager, 
            std::shared_ptr<TextManager> _textManager);
        ~MainMenuScene() = default;
        void update(float dt) override;
        SceneType handleInput(float dt) override;
        SceneType getType() const override
        {
            return SceneType::MAINMENU;
        }
    private:
        void draw() override;
        std::vector<std::string> menuOptions;
        std::vector<std::string> menuDescOptions;
        int selectedIndex = 0;
        float lineSpacing = 28.f;
        int arrowIndex = 0;
        int menuItemCount = 5;
        float yStart = 0.f;
        float lineHeight = 0.f;
};

#endif
