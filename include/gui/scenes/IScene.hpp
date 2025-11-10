/*
** EPITECH PROJECT, 2025
** zappy_graphical
** File description:
** Scene
*/

#ifndef _ISCENE_HPP_
    #define _ISCENE_HPP_

    enum class SceneType
    {
        NONE,
        TITLESCREEN,
        MAINMENU,
        MENU_SETTINGS,
        MENU_THEME,
        MENU_LANGUAGE,
        MENU_POKEDEX,
        GAMEPLAY,
        EXIT
    };

    class IScene
    {
        public:
            virtual ~IScene() = default;
            virtual void update(float dt) = 0;
            virtual SceneType handleInput(float dt) = 0;
            virtual SceneType getType() const = 0;
            virtual void onExit() {}
        private:
            virtual void draw() = 0;
    };

#endif
