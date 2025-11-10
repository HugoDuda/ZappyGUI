/*
** EPITECH PROJECT, 2025
** *
** File description:
** LanguageScreenScene
*/

#ifndef _LANGUAGE_SCREEN_SCENE_HPP_
    #define _LANGUAGE_SCREEN_SCENE_HPP_

    #include <vector>

    #include "scenes/AScene.hpp"

class LanguageScreenScene : public AScene
{
    public:
        LanguageScreenScene(std::shared_ptr<TextureManager> textureManager,
            std::shared_ptr<TextManager> textManager);
        ~LanguageScreenScene() = default;
        void update(float dt) override;
        SceneType handleInput(float dt) override;
        std::vector<std::string> languagesParser();
        std::string removeTxtExtension(const std::string &filename);
        SceneType getType() const override
        {
            return SceneType::MENU_LANGUAGE;
        }
        private:
            void draw() override;
            int menuItemCount;
            float yStart;
            float lineHeight;
            int arrowIndex;
            std::vector<std::string> languages;
};

#endif
