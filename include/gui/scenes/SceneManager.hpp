/*
** EPITECH PROJECT, 2025
** *
** File description:
** SceneManager
*/

#ifndef _SCENE_MANAGER_HPP_
    #define _SCENE_MANAGER_HPP_

    #include <unordered_map>
    #include <vector>
    #include <string>
    #include <functional>
    #include <exception>
    #include <iostream>

    #include "scenes/AScene.hpp"

typedef struct {
    bool isAnimation = true;
    bool isMusic = true;
    bool isSound = true;
} settings_t;

class SceneManager
{
    public:
        SceneManager() = default;
        ~SceneManager() = default;
        class SceneManagerException : public std::exception
        {
            public:
                explicit SceneManagerException(const std::string &message)
                : _message("[SCENEMANAGER] " + message)
                {}
                ~SceneManagerException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
        /**
         * @brief Get the currently active scene.
         * 
         * @return Pointer to current IScene, or nullptr if none.
         */
        IScene *getCurrentScene() const
        {
            return _currentScene;
        }
        /**
         * @brief Switch to a scene by type, creating it if needed.
         * 
         * @param type SceneType to switch to.
         * @throws SceneManagerException If no factory registered or creation fails.
         */
        void switchTo(SceneType type)
        {
            if (type == SceneType::NONE) {
                return;
            }
            if (_currentScene && _currentScene->getType() == SceneType::TITLESCREEN) {
                _currentScene->onExit();
                _sceneMap.erase(_currentScene->getType());
                _currentScene = nullptr;
            }
            if (_sceneMap.find(type) == _sceneMap.end()) {
                auto it = _creators.find(type);
                if (it == _creators.end()) {
                    throw SceneManagerException("No factory register.");
                }
                try {
                    _sceneMap[type] = it->second();
                } catch (const AScene::ASceneException &e) {
                    throw SceneManagerException("Can't switch scene.");
                }
            }
            _currentScene = _sceneMap[type].get();
        }
        /**
         * @brief Add an existing scene instance.
         * 
         * @param newScene Unique pointer to scene to add.
         */
        void addScene(std::unique_ptr<IScene> newScene)
        {
            _sceneMap[newScene->getType()] = std::move(newScene);
        }
        /**
         * @brief Register a factory function for a scene type.
         * 
         * @param type SceneType to register.
         * @param creator Factory returning a new scene instance.
         */
        void registerFactory(SceneType type,
            std::function<std::unique_ptr<IScene>()> creator)
        {
            _creators[type] = std::move(creator);
        }
        /**
         * @brief Remove all scenes and reset current scene.
         */
        void clearAll()
        {
            _sceneMap.clear();
            _currentScene = nullptr;
        }
    private:
        IScene *_currentScene = nullptr;
        std::unordered_map<SceneType, std::unique_ptr<IScene>> _sceneMap;
        std::unordered_map<SceneType, std::function<std::unique_ptr<IScene>()>> _creators;
};

class SettingsScreenScene : public AScene
{
    public:
        SettingsScreenScene(std::shared_ptr<TextureManager> textureManager,
            std::shared_ptr<TextManager> textManager, settings_t *settings);
        ~SettingsScreenScene() = default;
        void update(float dt) override;
        SceneType handleInput(float dt) override;
        SceneType getType() const override
        {
            return SceneType::MENU_SETTINGS;
        }
    private:
        void draw() override;
        std::vector<std::string> settingsOptions;
        std::vector<std::string> settingsStat;
        int menuItemCount;
        float yStart;
        float lineHeight;
        int arrowIndex;
        settings_t *_settings;
};

#endif
