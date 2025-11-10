/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** argsHandler
*/

#include "parser/Args.hpp"
#include <iostream>
#include <cstdlib>

args_t parseArguments(int argc, const char *const argv[])
{
    args_t args;
    std::string token;

    if (argc == 1) {
        throw ArgsExecption("No option found.");
    }
    for (int i = 1; i < argc; ++i) {
        token = argv[i];
        if (token == "-p") {
            if (i + 1 >= argc) {
                throw ArgsExecption("-p option need a arguement <port>.");
            }
            try {
                args.port = std::stoi(argv[++i]);
            } catch (...) {
                throw ArgsExecption("Port value invalid : " + static_cast<std::string>(argv[i]));
            }
        }
        else if (token == "-h") {
            if (i + 1 >= argc) {
                throw ArgsExecption("-h option need a argument <machine>.");
            }
            args.host = argv[++i];
        }
        else if (token == "--help" || token == "-help") {
            throw ArgsExecption("-h option need a argument <machine>.");
        }
        else {
            throw ArgsExecption("Unknown option : ");
        }
    }
    if (!args.showHelp) {
        if (args.port == 0) {
            throw ArgsExecption("Port is missing (-p <port>).");
        }
        if (args.host.empty()) {
            throw ArgsExecption("Machine adresse is missing (-h <machine>).");
        }
    }
    return args;
}
