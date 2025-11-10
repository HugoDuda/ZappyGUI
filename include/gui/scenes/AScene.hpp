/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** AScene
*/

#ifndef _ASCENE_HPP_
    #define _ASCENE_HPP_

    #include "scenes/IScene.hpp"
    #include "managers/TextureManager.hpp"

class AScene : public IScene {
    public:
        AScene(std::shared_ptr<TextureManager> textureManager,
            std::shared_ptr<TextManager> textManager, bool isMenuInterface)
            : _textureManager(std::move(textureManager)), _textManager(std::move(textManager)),
            _isMenuInterface(isMenuInterface), _path(getRandomBackground())
        {}
        class ASceneException : public std::exception
        {
            public:
                explicit ASceneException(const std::string &message)
                : _message("[SCENE] " + message)
                {}
                ~ASceneException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        virtual ~AScene() = default;
        virtual void update(float dt) = 0;
        virtual SceneType handleInput(float dt) = 0;
        virtual SceneType getType() const = 0;
        std::string getRandomBackground()
        {
            static bool sRandInitialized = false;

            if (!sRandInitialized) {
                srand(static_cast<unsigned>(time(nullptr)));
                sRandInitialized = true;
            }
            int index = (rand() % 6) + 1;
            return "resources/menu/background" + std::to_string(index) + ".png";
        }
        void setTheme(const std::string &dungeonName)
        {
            themeFile = "resources/dungeon/" + dungeonName;
        }
        std::string getTheme() const
        {
            return themeFile;
        }
        void displayMenuInterface(const std::string &interfaceName)
        {
            Texture2D &background = _textureManager->getTexture(_path);
            Texture2D &settings = _textureManager->getTexture("resources/menu/settings.png");
            float scaleX = (float)screenW / background.width;
            float scaleSettingsY = (float)screenH / settings.height;

            DrawTextureEx(background, {0.f, 0.f}, 0.f, scaleX, WHITE);
            DrawTextureEx(settings, {0.f, 0.f}, 0.f, scaleSettingsY, WHITE);
            _textManager->drawCode(interfaceName, {150.f, 40.f}, 70.f);
        }
    protected:
        int screenW = GetScreenWidth();
        int screenH = GetScreenHeight();
        static std::string themeFile;
        std::shared_ptr<TextureManager> _textureManager;
        std::shared_ptr<TextManager> _textManager;
        bool _isMenuInterface;
        std::string _path;
    private:
        virtual void draw() = 0;
};

#endif
