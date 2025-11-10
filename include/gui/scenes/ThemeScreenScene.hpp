/*
** EPITECH PROJECT, 2025
** *
** File description:
** ThemeScreenScene
*/

#ifndef _THEME_SCREEN_SCENE_HPP_
    #define _THEME_SCREEN_SCENE_HPP_

    #include <vector>

    #include "scenes/AScene.hpp"

class ThemeScreenScene : public AScene
{
    public:
        ThemeScreenScene(std::shared_ptr<TextureManager> TextureManager,
            std::shared_ptr<TextManager> textManager);
        ~ThemeScreenScene() = default;
        void update(float dt) override;
        SceneType handleInput(float dt) override;
        SceneType getType() const override
        {
            return SceneType::MENU_THEME;
        }
        private:
            void draw() override;
            std::vector<std::string> themeParser();
            std::string removePngExtension(const std::string &filename);
            int menuItemCount;
            float yStart;
            float lineHeight;
            int arrowIndex;
            std::vector<std::string> themeOptions;
            std::vector<Texture2D> dungeonsPreview;
};

#endif
