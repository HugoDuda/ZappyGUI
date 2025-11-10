/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Window
*/

#ifndef _WINDOW_HPP_
    #define _WINDOW_HPP_

    #include "managers/SoundManager.hpp"
    #include "scenes/SceneManager.hpp"
    #include <exception>

class Window
{
    public:
        /**
         * @brief Constructs the main application window, initializes core resources and starts the first scene.
         * 
         * @param screenWidth Window width in pixels.
         * @param screenHeight Window height in pixels.
         * @param fps Target frames per second.
         * @param port Network port to use.
         * @param host Host address to connect.
         * @throws WindowException If audio, text, or scene initialization fails.
         */
        Window(int screenWidth, int screenHeight, int fps, int port, const std::string &host);
        /**
         * @brief Releases all window and audio resources on destruction.
         */
        ~Window();
        /**
         * @brief Main application loop: processes events and draws the current scene until exit.
         */
        void run();
        /**
         * @brief Registers all available scene factories for the application.
         */
        void sceneRegister();
        class WindowException : public std::exception
        {
            public:
                explicit WindowException(const std::string &message)
                : _message("[WINDOW] " + message)
                {}
                ~WindowException() override = default;
                const char *what() const noexcept override
                {
                    return _message.c_str();
                }
            private:
                std::string _message;
        };
    private:
        /**
         * @brief Handles scene input, updates the active scene and manages music transitions.
         *
         * @param dt Delta time (time since last frame).
         * @return true if the application should exit, false otherwise.
         */
        bool sceneHandler(float dt);
        const int SCREENWIDTH;
        const int SCREENHEIGHT;
        const int FPS;
        const int PORT;
        const std::string HOST;
        SceneManager sceneManager;
        std::shared_ptr<TextureManager> textureManager;
        std::shared_ptr<TextManager> textManager;
        std::shared_ptr<SoundManager> soundManager;
        settings_t _settings;
};

#endif
