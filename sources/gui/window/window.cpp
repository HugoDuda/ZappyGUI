/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Window
*/

#include "Window.hpp"
#include "scenes/AScene.hpp"
#include "scenes/TitleScreenScene.hpp"
#include "scenes/LanguageScreenScene.hpp"
#include "scenes/ThemeScreenScene.hpp"
#include "scenes/MenuScene.hpp"
#include "scenes/GameScene.hpp"
#include <iostream>

Window::Window(int screenWidth, int screenHeight, int fps, int port, const std::string &host)
    : SCREENWIDTH(screenWidth), SCREENHEIGHT(screenHeight), FPS(fps), PORT(port), HOST(host)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Zappy Graphical");
    SetExitKey(0);
    SetTargetFPS(FPS);
    InitAudioDevice();
    textureManager = std::make_shared<TextureManager>();
    soundManager = std::make_shared<SoundManager>();
    try {
        soundManager->getMusic("resources/music/TitleScreen.mp3");
        soundManager->getMusic("resources/music/MainMenu.mp3");
    } catch (const SoundManager::SoundManagerException &e) {
        std::cerr << e.what() << std::endl;
        Window::~Window();
        throw Window::WindowException("SoundManager error.");
    }
    PlayMusicStream(soundManager->getMusic("resources/music/TitleScreen.mp3"));
    try {
        textManager = std::make_shared<TextManager>("resources/mainFont.ttf", 32);
        textManager->loadLanguage("English");
    } catch (const TextManager::TextManagerException &e) {
        std::cerr << e.what() << std::endl;
        Window::~Window();
        throw Window::WindowException("TextManager error.");
    }
    sceneRegister();
    try {
        sceneManager.switchTo(SceneType::TITLESCREEN);
    } catch (const SceneManager::SceneManagerException &e) {
        std::cerr << e.what() << std::endl;
        Window::~Window();
        throw WindowException("Can't load title screen.");
    }
}

void Window::sceneRegister()
{
    sceneManager.registerFactory(
        SceneType::TITLESCREEN,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<TitleScreenScene>(textureManager);
        }
    );
    sceneManager.registerFactory(
        SceneType::MAINMENU,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<MainMenuScene>(textureManager, textManager);
        }
    );
    sceneManager.registerFactory(
        SceneType::GAMEPLAY,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<GameScene>(textureManager, textManager,
            SCREENWIDTH, SCREENHEIGHT, soundManager, PORT, HOST, &_settings);
        }
    );
    sceneManager.registerFactory(
        SceneType::MENU_SETTINGS,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<SettingsScreenScene>(textureManager, textManager, &_settings);
        }
    );
    sceneManager.registerFactory(
        SceneType::MENU_THEME,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<ThemeScreenScene>(textureManager, textManager);
        }
    );
    sceneManager.registerFactory(
        SceneType::MENU_LANGUAGE,
        [this]() -> std::unique_ptr<IScene> {
            return std::make_unique<LanguageScreenScene>(textureManager, textManager);
        }
    );
}

#undef SUPPORT_MODULE_RTEXT

Window::~Window()
{
    soundManager.reset();
    CloseAudioDevice();
    textManager.reset();
    textureManager.reset();
}

bool Window::sceneHandler(float dt)
{
    if (auto scene = sceneManager.getCurrentScene()) {
        SceneType type = scene->handleInput(dt);
        if (scene->getType() == SceneType::TITLESCREEN) {
            UpdateMusicStream(soundManager->getMusic("resources/music/TitleScreen.mp3"));
        } else if (scene->getType() != SceneType::GAMEPLAY && _settings.isMusic) {
            UpdateMusicStream(soundManager->getMusic("resources/music/MainMenu.mp3"));
        }
        if (type != SceneType::NONE) {
            if (type != SceneType::TITLESCREEN && type != SceneType::GAMEPLAY) {
                if (_settings.isMusic) {
                    PlayMusicStream(soundManager->getMusic("resources/music/MainMenu.mp3"));
                }
            } else {
                StopMusicStream(soundManager->getMusic("resources/music/MainMenu.mp3"));
            }
            if (type == SceneType::EXIT) {
                return true;
            }
            try {
                sceneManager.switchTo(type);
            } catch (const SceneManager::SceneManagerException &e) {
                return true;
            }
            return false;
        }
        try {
            scene->update(dt);
        } catch (const AScene::ASceneException& ass) {
            std::cerr << "[FATAL]: "<< ass.what() << std::endl;
            return true;
        }
    }
    return false;
}

void Window::run()
{
    float dt = 0;

    while (WindowShouldClose() == false) {
        dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(BLACK);
        if (sceneHandler(dt) == true) {
            break;
        }
        EndDrawing();
    }
}
