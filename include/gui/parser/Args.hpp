/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Args
*/

#ifndef _ARGS_HPP_
    #define _ARGS_HPP_

    #include <string>
    #include <exception>

typedef struct {
    bool showHelp = false;
    int port = 0;
    std::string host;
} args_t;

class ArgsExecption : public std::exception
{
    public:
        explicit ArgsExecption(const std::string &message)
        : _message("[ARGUMENTS] " + message)
        {}
        ~ArgsExecption() override = default;
        const char *what() const noexcept override
        {
            return _message.c_str();
        }
    private:
        const std::string _message;
};

/**
 * @brief Parses command line arguments for host and port.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Parsed arguments structure.
 * @throws ArgsExecption If an option is missing, unknown or invalid.
 */
args_t parseArguments(int argc, const char *const argv[]);

#endif
