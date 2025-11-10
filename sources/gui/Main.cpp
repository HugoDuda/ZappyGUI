/*
** EPITECH PROJECT, 2025
** B-YEP-400
** File description:
** main
*/

#include "parser/Args.hpp"
#include "Window.hpp"
#include <iostream>

#define SUCCESS 0
#define ERROR 84

int main(int argc, const char *const argv[])
{
    args_t args = {false, 0, ""};

    try {
        args = parseArguments(argc, argv);
    } catch (const ArgsExecption &e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    try {
        Window window(1920, 1080, 500, args.port, args.host);
        window.run();
    } catch (const Window::WindowException &e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    CloseWindow();
    return SUCCESS;
}
